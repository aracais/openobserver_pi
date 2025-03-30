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

ooControlDialogImpl::ooControlDialogImpl(wxWindow* parent) 
    : ooControlDialogDef(parent), m_MiniPanel(nullptr), m_Observations(nullptr), m_ObservationsTable(nullptr)
{
#if wxCHECK_VERSION(3,0,0)
    SetLayoutAdaptationMode(wxDIALOG_ADAPTATION_MODE_ENABLED);
#endif // wxCHECK_VERSION(3,0,0)

    m_MiniPanel = new ooMiniPanel(m_panelObservations);
    bSizerTopButtons->Add(m_MiniPanel, 1, wxEXPAND, 5);
    m_panelObservations->Layout();
	m_fgSizerObservations->Fit(m_panelObservations);

    wxFileName backup(*g_pData, "observations.xml");
    m_BackupFilename = backup.GetFullPath();

    // bind timers
    m_BackupTimer.Bind(wxEVT_TIMER, &ooControlDialogImpl::OnBackupTimer, this, m_BackupTimer.GetId());
}

ooControlDialogImpl::~ooControlDialogImpl()
{
    m_BackupTimer.Stop();

    if (!m_Observations) return;

    wxFileOutputStream output_stream(m_BackupFilename);
    
    if (!output_stream.IsOk())
    {
        wxLogError("Could not save observations to file '%s'.", m_BackupFilename);
        return;
    }

    m_Observations->SaveToXML(output_stream.GetFile());

}

void ooControlDialogImpl::CreateObservationsTable(ooObservations *observations)
{
    m_Observations = observations;

    m_ObservationsTable = new wxGrid(m_panelObservations, wxID_ANY, wxDefaultPosition, wxSize(740, 465), 0);
    m_ObservationsTable->AssignTable(m_Observations);
    m_ObservationsTable->SetColSizes(m_Observations->GetColSizes());

	// Grid
	m_ObservationsTable->EnableEditing( true );
	m_ObservationsTable->EnableGridLines( true );
	m_ObservationsTable->EnableDragGridSize( false );
	m_ObservationsTable->SetMargins( 0, 0 );

	// Columns
	m_ObservationsTable->EnableDragColMove( false );
	m_ObservationsTable->EnableDragColSize( true );
	m_ObservationsTable->SetColLabelSize( wxGRID_AUTOSIZE );
	m_ObservationsTable->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_ObservationsTable->EnableDragRowSize( false );
	m_ObservationsTable->SetRowLabelSize( 0 );
	m_ObservationsTable->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance
	m_ObservationsTable->SetLabelFont( wxFont( 11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	// Cell Defaults
	m_ObservationsTable->SetDefaultCellFont( wxFont( 11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_ObservationsTable->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );

    wxGridCellAutoWrapStringEditor *editor = new wxGridCellAutoWrapStringEditor();
    m_ObservationsTable->SetDefaultEditor(editor);
    
    wxGridCellAutoWrapStringRenderer *renderer = new wxGridCellAutoWrapStringRenderer();
    m_ObservationsTable->SetDefaultRenderer(renderer);

    // m_ObservationsTable is a wxGrid, ultimately derived from wxWindow
	m_fgSizerObservations->Add(m_ObservationsTable, 0, wxALL|wxEXPAND, 5);

    // restore observations
    if (!m_Observations->ReadFromXML(m_BackupFilename))
    {
        wxMessageBox("Error loading observations file " + m_BackupFilename + ".", "Error", wxOK, this);
    }

    // start timer to backup observations every 30 seconds
    m_BackupTimer.Start(30000); // 30'000 ms = 30 s
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

void ooControlDialogImpl::OnButtonClickNewObservation( wxCommandEvent& event )
{
    if (!m_Observations) return;

    m_Observations->InsertRows(0, 1);
}

void ooControlDialogImpl::OnButtonClickDeleteObservation( wxCommandEvent& event )
{
    if (!m_Observations) return;

    if (m_Observations->GetNumberRows() > 0)
        m_Observations->DeleteRows(0);
}

void ooControlDialogImpl::OnButtonClickExportObservations( wxCommandEvent& event )
{
    if (!m_Observations) return;

    wxFileDialog exportFileDialog(this, _("Export observations to CSV file"), "", m_ObservationsDate->GetValue(), "CSV file (*.csv)|*.csv", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
 
    if (exportFileDialog.ShowModal() == wxID_CANCEL)
        return;
 
    wxFileOutputStream output_stream(exportFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxMessageBox("Unable to save observations to file " + exportFileDialog.GetPath() + ".", "Error", wxOK, this);
        return;
    }

    m_Observations->SaveToCSV(output_stream.GetFile());
}

void ooControlDialogImpl::OnBackupTimer(wxTimerEvent& event)
{
    if (!m_Observations) return;

    wxFileOutputStream output_stream(m_BackupFilename);
    
    if (!output_stream.IsOk())
    {
        wxLogError("Could not save observations to file '%s'.", m_BackupFilename);
        return;
    }

    m_Observations->SaveToXML(output_stream.GetFile());
}

void ooControlDialogImpl::OnButtonClickObservationsAddMarks( wxCommandEvent& event )
{
    if (!m_Observations) return;

    m_Observations->AddMarks();

    m_ObservationsTable->ForceRefresh();
}

void ooControlDialogImpl::OnButtonClickObservationsDeleteMarks( wxCommandEvent& event )
{
    if (!m_Observations) return;

    m_Observations->DeleteMarks();

    m_ObservationsTable->ForceRefresh();
}

void ooControlDialogImpl::ooControlCloseClick(wxCommandEvent& event)
{
    g_openobserver_pi->ToggleToolbarIcon();
}

void ooControlDialogImpl::ooControlDialogDefOnClose(wxCloseEvent& event)
{
    g_openobserver_pi->ToggleToolbarIcon();
}
