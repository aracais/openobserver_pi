///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ooControlDialogDef.h"

///////////////////////////////////////////////////////////////////////////

ooControlDialogDef::ooControlDialogDef()
{
}

ooControlDialogDef::ooControlDialogDef( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
{
	this->Create( parent, id, title, pos, size, style );
}

bool ooControlDialogDef::Create( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
{
	if ( !wxDialog::Create( parent, id, title, pos, size, style ) )
	{
		return false;
	}

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_SizerControl = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 0, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_notebookControl = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelProject = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebookControl->AddPage( m_panelProject, _("Project"), false );
	m_panelObservations = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizerObservations;
	fgSizerObservations = new wxFlexGridSizer( 3, 1, 0, 0 );
	fgSizerObservations->SetFlexibleDirection( wxBOTH );
	fgSizerObservations->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizerObservationsLabels;
	fgSizerObservationsLabels = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizerObservationsLabels->SetFlexibleDirection( wxBOTH );
	fgSizerObservationsLabels->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_ObservationsDateLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsDateLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsDateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsDate = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsLabels->Add( m_ObservationsDate, 1, wxALL, 5 );

	m_ObservationsTimeLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Time (UTC):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsTimeLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsTimeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsTime = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsLabels->Add( m_ObservationsTime, 1, wxALL, 5 );

	m_ObservationsLatLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Lat:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsLatLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsLatLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsLat = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsLabels->Add( m_ObservationsLat, 1, wxALL, 5 );

	m_ObservationsLonLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Lon:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsLonLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsLonLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsLon = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsLabels->Add( m_ObservationsLon, 1, wxALL, 5 );


	fgSizerObservations->Add( fgSizerObservationsLabels, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizerObservationsButtons;
	fgSizerObservationsButtons = new wxFlexGridSizer( 1, 5, 0, 0 );
	fgSizerObservationsButtons->SetFlexibleDirection( wxBOTH );
	fgSizerObservationsButtons->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_ObservationsNew = new wxButton( m_panelObservations, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsNew, 0, wxALL, 5 );

	m_ObservationsDelete = new wxButton( m_panelObservations, wxID_ANY, _("Delete Last"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsDelete, 0, wxALL, 5 );

	m_ObservationsExportObservations = new wxButton( m_panelObservations, wxID_ANY, _("Export CSV"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsExportObservations, 0, wxALL, 5 );

	m_ObservationsAddMarks = new wxButton( m_panelObservations, wxID_ANY, _("Add Marks"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsAddMarks, 0, wxALL, 5 );

	m_ObservationsDeleteMarks = new wxButton( m_panelObservations, wxID_ANY, _("Delete Marks"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsDeleteMarks, 0, wxALL, 5 );


	fgSizerObservations->Add( fgSizerObservationsButtons, 1, 0, 5 );

	m_ObservationsTable = new wxGrid( m_panelObservations, wxID_ANY, wxDefaultPosition, wxSize( 740,500 ), 0 );

	// Grid
	m_ObservationsTable->CreateGrid( 0, 7 );
	m_ObservationsTable->EnableEditing( true );
	m_ObservationsTable->EnableGridLines( true );
	m_ObservationsTable->EnableDragGridSize( false );
	m_ObservationsTable->SetMargins( 0, 0 );

	// Columns
	m_ObservationsTable->SetColSize( 0, 70 );
	m_ObservationsTable->SetColSize( 1, 70 );
	m_ObservationsTable->SetColSize( 2, 90 );
	m_ObservationsTable->SetColSize( 3, 90 );
	m_ObservationsTable->SetColSize( 4, 100 );
	m_ObservationsTable->SetColSize( 5, 200 );
	m_ObservationsTable->SetColSize( 6, 70 );
	m_ObservationsTable->EnableDragColMove( false );
	m_ObservationsTable->EnableDragColSize( true );
	m_ObservationsTable->SetColLabelValue( 0, _("Date") );
	m_ObservationsTable->SetColLabelValue( 1, _("Time (UTC)") );
	m_ObservationsTable->SetColLabelValue( 2, _("Lat") );
	m_ObservationsTable->SetColLabelValue( 3, _("Lon") );
	m_ObservationsTable->SetColLabelValue( 4, _("Species") );
	m_ObservationsTable->SetColLabelValue( 5, _("Notes") );
	m_ObservationsTable->SetColLabelValue( 6, _("Mark GUID") );
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
	fgSizerObservations->Add( m_ObservationsTable, 0, wxALL|wxEXPAND, 5 );


	m_panelObservations->SetSizer( fgSizerObservations );
	m_panelObservations->Layout();
	fgSizerObservations->Fit( m_panelObservations );
	m_notebookControl->AddPage( m_panelObservations, _("Observations"), true );

	fgSizer3->Add( m_notebookControl, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 0, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizerOKCancel;
	bSizerOKCancel = new wxBoxSizer( wxHORIZONTAL );

	m_buttonOpenMiniWindow = new wxButton( this, wxID_ANY, _("Open &Mini Window"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerOKCancel->Add( m_buttonOpenMiniWindow, 0, wxALL, 5 );

	m_buttonClose = new wxButton( this, wxID_ANY, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerOKCancel->Add( m_buttonClose, 0, wxALL, 5 );


	fgSizer4->Add( bSizerOKCancel, 1, wxEXPAND, 5 );


	fgSizer3->Add( fgSizer4, 1, wxEXPAND, 5 );


	m_SizerControl->Add( fgSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( m_SizerControl );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_ObservationsNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickNewObservation ), NULL, this );
	m_ObservationsDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickDeleteObservation ), NULL, this );
	m_ObservationsExportObservations->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickExportObservations ), NULL, this );
	m_ObservationsAddMarks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsAddMarks ), NULL, this );
	m_ObservationsDeleteMarks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsDeleteMarks ), NULL, this );
	m_buttonOpenMiniWindow->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::ooControlOpenMiniWindowClick ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::ooControlCloseClick ), NULL, this );

	return true;
}

ooControlDialogDef::~ooControlDialogDef()
{
	// Disconnect Events
	m_ObservationsNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickNewObservation ), NULL, this );
	m_ObservationsDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickDeleteObservation ), NULL, this );
	m_ObservationsExportObservations->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickExportObservations ), NULL, this );
	m_ObservationsAddMarks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsAddMarks ), NULL, this );
	m_ObservationsDeleteMarks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsDeleteMarks ), NULL, this );
	m_buttonOpenMiniWindow->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::ooControlOpenMiniWindowClick ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::ooControlCloseClick ), NULL, this );

}
