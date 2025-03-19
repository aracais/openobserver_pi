/**************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  OpenObserver Plugin Control Dialog
 * Author:   Jon Gough
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 **************************************************************************/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/file.h>

#include <wx/base64.h>
#include <wx/mstream.h>

#include "ooControlDialogImpl.h"
#include "openobserver_pi.h"

#include "ocpn_plugin.h"

#if wxCHECK_VERSION(3,0,0)
#include <wx/valnum.h>
#endif

#include <wx/fontdlg.h>

extern openobserver_pi    *g_openobserver_pi;

ooControlDialogImpl::ooControlDialogImpl( wxWindow* parent ) : ooControlDialogDef( parent )
{
#if wxCHECK_VERSION(3,0,0)
    SetLayoutAdaptationMode(wxDIALOG_ADAPTATION_MODE_ENABLED);
#endif // wxCHECK_VERSION(3,0,0)

    wxGridCellAutoWrapStringEditor *editor = new wxGridCellAutoWrapStringEditor();
    m_ObservationsTable->SetDefaultEditor(editor);
    wxGridCellAutoWrapStringRenderer *renderer = new wxGridCellAutoWrapStringRenderer();
    m_ObservationsTable->SetDefaultRenderer(renderer);
}

void ooControlDialogImpl::OnButtonClickNewObservation( wxCommandEvent& event )
{
    m_ObservationsTable->InsertRows(0, 1);
    m_ObservationsTable->SetCellValue(0, 0, m_ObservationsDate->GetValue());
    m_ObservationsTable->SetCellValue(0, 1, m_ObservationsTime->GetValue());
    m_ObservationsTable->SetCellValue(0, 2, m_ObservationsLat->GetValue());
    m_ObservationsTable->SetCellValue(0, 3, m_ObservationsLon->GetValue());
}

void ooControlDialogImpl::OnButtonClickDeleteObservation( wxCommandEvent& event )
{
    if (m_ObservationsTable->GetNumberRows() > 0)
        m_ObservationsTable->DeleteRows(0);
}

void ooControlDialogImpl::OnButtonClickExportObservations( wxCommandEvent& event )
{
    wxFileDialog exportFileDialog(this, _("Export observations to CSV file"), "", m_ObservationsDate->GetValue(), "CSV file (*.csv)|*.csv", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
 
    if (exportFileDialog.ShowModal() == wxID_CANCEL)
        return;
 
    // save the current contents in the file;
    // this can be done with e.g. wxWidgets output streams:
    wxFileOutputStream output_stream(exportFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", exportFileDialog.GetPath());
        return;
    }

    wxFile *file = output_stream.GetFile();

    const int exportCols = m_ObservationsTable->GetNumberCols();
    
    for (int c=0; c < exportCols; ++c)
    {
        file->Write(m_ObservationsTable->GetColLabelValue(c));

        if (c < (exportCols - 1))
            file->Write(",");
    }
    file->Write("\n");

    for (int r=0; r < m_ObservationsTable->GetNumberRows(); ++r)
    {
        for (int c=0; c < exportCols; ++c)
        {
            file->Write(m_ObservationsTable->GetCellValue(r, c));

            if (c < (exportCols - 1))
                file->Write(",");
        }
        file->Write("\n");
    }

    file->Close();
}

void ooControlDialogImpl::OnButtonClickObservationsAddMarks( wxCommandEvent& event )
{
    const int dateCol = 0;
    const int timeCol = 1;
    const int latCol = 2;
    const int lonCol = 3;
    const int speciesCol = 4;
    const int notesCol = 5;
    const int markGUIDCol = 6;

    for (int r=0; r < m_ObservationsTable->GetNumberRows(); ++r)
    {
        if (m_ObservationsTable->GetCellValue(r, markGUIDCol).IsEmpty())
        {
            wxDateTime datetime;
            datetime.ParseISODate(m_ObservationsTable->GetCellValue(r, dateCol));
            datetime.ParseISOTime(m_ObservationsTable->GetCellValue(r, timeCol));
            double lat = fromDMM_Plugin(m_ObservationsTable->GetCellValue(r, latCol));
            double lon = fromDMM_Plugin(m_ObservationsTable->GetCellValue(r, lonCol));
            wxString name = m_ObservationsTable->GetCellValue(r, speciesCol) + " (OO)";
            wxString description = m_ObservationsTable->GetCellValue(r, notesCol);
            wxString guid = GetNewGUID();

            // add waypoint
            PlugIn_Waypoint wp(lat, lon, "fish", name, guid);
            wp.m_MarkDescription = description;
            wp.m_CreateTime = datetime;
            AddSingleWaypoint(&wp);

            // store guid in table
            m_ObservationsTable->SetCellValue(r, markGUIDCol, guid);
        }
    }
}

void ooControlDialogImpl::OnButtonClickObservationsDeleteMarks( wxCommandEvent& event )
{
    const int markGUIDCol = 6;
    for (int r=0; r < m_ObservationsTable->GetNumberRows(); ++r)
    {
        wxString guid = m_ObservationsTable->GetCellValue(r, markGUIDCol);
        if (guid.IsEmpty()) continue;

        // delete waypoint
        DeleteSingleWaypoint(guid);

        // remove guid from table
        guid.Clear();
        m_ObservationsTable->SetCellValue(r, markGUIDCol, guid);
    }
}

void ooControlDialogImpl::ooControlCloseClick( wxCommandEvent& event )
{
    g_openobserver_pi->ToggleToolbarIcon();

    Show(false);
}

void ooControlDialogImpl::SetPositionFix( time_t fixTime, double lat, double lon )
{
    char dateString[16];
    std::strftime(dateString, 16, "%F", gmtime(&fixTime));
    char timeString[16];
    std::strftime(timeString, 16, "%T", gmtime(&fixTime));

    m_ObservationsDate->SetValue(dateString);
    m_ObservationsTime->SetValue(timeString);
    m_ObservationsLat->SetValue(toSDMM_PlugIn(1, lat));
    m_ObservationsLon->SetValue(toSDMM_PlugIn(2, lon));
}
