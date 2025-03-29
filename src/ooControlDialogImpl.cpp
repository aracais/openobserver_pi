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
#include <wx/msgdlg.h>
#include <wx/sstream.h>
#include <wx/wfstream.h>
#include <wx/file.h>

#include <wx/xml/xml.h>

#include <wx/base64.h>
#include <wx/mstream.h>

#include "ooControlDialogImpl.h"
#include "openobserver_pi.h"

#include "ocpn_plugin.h"

#if wxCHECK_VERSION(3,0,0)
#include <wx/valnum.h>
#endif

#include <wx/fontdlg.h>

extern openobserver_pi *g_openobserver_pi;
extern wxString *g_pData;

ooControlDialogImpl::ooControlDialogImpl(wxWindow* parent) : ooControlDialogDef(parent)
{
#if wxCHECK_VERSION(3,0,0)
    SetLayoutAdaptationMode(wxDIALOG_ADAPTATION_MODE_ENABLED);
#endif // wxCHECK_VERSION(3,0,0)

    wxGridCellAutoWrapStringEditor *editor = new wxGridCellAutoWrapStringEditor();
    m_ObservationsTable->SetDefaultEditor(editor);
    wxGridCellAutoWrapStringRenderer *renderer = new wxGridCellAutoWrapStringRenderer();
    m_ObservationsTable->SetDefaultRenderer(renderer);

    // restore observations
    wxFileName backup(*g_pData, "observations.xml");
    m_BackupFilename = backup.GetFullPath();
    read_observations_from_xml(m_BackupFilename);

    // start timer to backup observations every 30 seconds
    m_BackupTimer.Bind(wxEVT_TIMER, &ooControlDialogImpl::OnBackupTimer, this, m_BackupTimer.GetId());
    m_BackupTimer.Start(30000); // 30'000 ms = 30 s

    m_ObservationDurationTimer.Bind(wxEVT_TIMER, &ooControlDialogImpl::OnObservationDurationTimer, this, m_ObservationDurationTimer.GetId());
}

ooControlDialogImpl::~ooControlDialogImpl()
{
    wxFileOutputStream output_stream(m_BackupFilename);
    
    if (!output_stream.IsOk())
    {
        wxLogError("Could not save observations to file '%s'.", m_BackupFilename);
        return;
    }

    save_observations_to_xml(output_stream.GetFile());
}

void ooControlDialogImpl::SetPositionFix(time_t fixTime, double lat, double lon)
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

void ooControlDialogImpl::ooControlStartStopObservationClick(wxCommandEvent& event)
{
    if (!m_ObservationDurationTimer.IsRunning()) 
    {
        // start observation
        m_StartStopObservation->SetLabel("Stop Observation");

        // start duration stopwatch
        m_ObservationDurationStopWatch.Start(0);

        // start timer to update observation duration
        m_ObservationDurationTimer.Start(100); // 100 ms = 0.1 s

        // create new observation in table and fill start date, time and position
        m_ObservationsTable->InsertRows(0, 1);
        m_ObservationsTable->SetCellValue(0, 0, m_ObservationsDate->GetValue());
        m_ObservationsTable->SetCellValue(0, 1, m_ObservationsTime->GetValue());
        m_ObservationsTable->SetCellValue(0, 2, m_ObservationsLat->GetValue());
        m_ObservationsTable->SetCellValue(0, 3, m_ObservationsLon->GetValue());
    } else {
        // stop observation
        m_StartStopObservation->SetLabel("Start Observation");

        m_ObservationDurationStopWatch.Pause();
        m_ObservationDurationTimer.Stop();

        // fill observation stop date, time and position
        // m_ObservationsTable->SetCellValue(0, 0, m_ObservationsDate->GetValue());
        // m_ObservationsTable->SetCellValue(0, 1, m_ObservationsTime->GetValue());
        // m_ObservationsTable->SetCellValue(0, 2, m_ObservationsLat->GetValue());
        // m_ObservationsTable->SetCellValue(0, 3, m_ObservationsLon->GetValue());
    }
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
 
    wxFileOutputStream output_stream(exportFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxMessageBox("Unable to save observations to file " + exportFileDialog.GetPath() + ".", "Error", wxOK, this);
        return;
    }

    save_observations_to_csv(output_stream.GetFile());
}

void ooControlDialogImpl::OnBackupTimer(wxTimerEvent& event)
{
    wxFileOutputStream output_stream(m_BackupFilename);
    
    if (!output_stream.IsOk())
    {
        wxLogError("Could not save observations to file '%s'.", m_BackupFilename);
        return;
    }

    save_observations_to_xml(output_stream.GetFile());
}

void ooControlDialogImpl::OnObservationDurationTimer(wxTimerEvent& event)
{
    const long duration_ms = m_ObservationDurationStopWatch.Time();

    const unsigned int hours = duration_ms / 3600000;
    const unsigned int minutes = (duration_ms % 3600000) / 60000;
    const unsigned int seconds = (duration_ms % 60000) / 1000;

    char durationString[16];
    std::sprintf(durationString, "%02u:%02u:%02u", hours, minutes, seconds);
    
    m_ObservationDuration->SetValue(durationString);
}

void ooControlDialogImpl::save_observations_to_csv(wxFile *file)
{
    const int C = m_ObservationsTable->GetNumberCols();
    const int R = m_ObservationsTable->GetNumberRows();
    
    for (int c=0; c<C; ++c)
    {
        file->Write("\"" + m_ObservationsTable->GetColLabelValue(c) + "\"");

        if (c<(C - 1))
            file->Write(",");
    }
    file->Write("\n");

    for (int r=0; r<R; ++r)
    {
        for (int c=0; c<C; ++c)
        {
            file->Write("\"" + m_ObservationsTable->GetCellValue(r, c) + "\"");

            if (c<(C - 1))
                file->Write(",");
        }
        file->Write("\n");
    }

    file->Close();
}

void ooControlDialogImpl::save_observations_to_xml(wxFile *file)
{
    const int C = m_ObservationsTable->GetNumberCols();
    const int R = m_ObservationsTable->GetNumberRows();

    wxXmlDocument xmlDoc;    
    wxXmlNode* observations = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "observations");
    observations->AddAttribute("creator", "OpenObserver for OpenCPN");
    xmlDoc.SetRoot(observations);
    
    for (int r=0; r<R; ++r) {
        wxXmlNode* observation = new wxXmlNode (observations, wxXML_ELEMENT_NODE, "observation");
        observation->AddAttribute("id", wxString::Format(wxT("%i"), r));

        for (int c=0; c<C; ++c) {
            wxXmlNode* field = new wxXmlNode(observation, wxXML_ELEMENT_NODE, "field");
            field->AddAttribute("id", wxString::Format(wxT("%i"), c));
            field->AddChild(new wxXmlNode(wxXML_TEXT_NODE, "",  m_ObservationsTable->GetCellValue(r, c)));
        }
    }
    
    // write the output to a wxString
    wxStringOutputStream stream;
    xmlDoc.Save(stream);

    // write the string to the file
    file->Write(stream.GetString());    
}

void ooControlDialogImpl::read_observations_from_xml(wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename)) {
        wxMessageBox("Error loading observations file " + filename + ".", "Error", wxOK, this);
        return;
    }

    if (xmlDoc.GetRoot()->GetName() != "observations") {
        wxMessageBox("Error loading observations file: no observations found.", "Error", wxOK, this);
        return;
    }

    const int C = m_ObservationsTable->GetNumberCols();
    wxXmlNode *observation = xmlDoc.GetRoot()->GetChildren();
    while (observation)
    {
        int r = -1;
        if (observation->GetAttribute("id").ToInt(&r) && (r>=0)) {

            // expand number of rows as needed to accommodate observations
            if (r >= m_ObservationsTable->GetNumberRows()) {
                m_ObservationsTable->AppendRows(r - m_ObservationsTable->GetNumberRows() + 1);
            }

            wxXmlNode *field = observation->GetChildren();
            while (field) {
                if (field->GetChildren()) {
                    int c = -1;
                    if (field->GetAttribute("id").ToInt(&c) && (c>=0) && (c<C)) {
                        m_ObservationsTable->SetCellValue(r, c, field->GetChildren()->GetContent());
                    }
                }

                field = field->GetNext();
            }
        }

        observation = observation->GetNext();
    }
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

void ooControlDialogImpl::ooControlOpenMiniWindowClick(wxCommandEvent& event)
{
    g_openobserver_pi->ToggleWindow();
}

void ooControlDialogImpl::ooControlCloseClick(wxCommandEvent& event)
{
    g_openobserver_pi->ToggleToolbarIcon();
}
