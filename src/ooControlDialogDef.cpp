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
	fgSizer3 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer3->AddGrowableCol( 0 );
	fgSizer3->AddGrowableRow( 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_notebookControl = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panelProject = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebookControl->AddPage( m_panelProject, _("Project"), false );
	m_panelObservations = new wxPanel( m_notebookControl, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_fgSizerObservations = new wxFlexGridSizer( 6, 1, 0, 0 );
	m_fgSizerObservations->SetFlexibleDirection( wxBOTH );
	m_fgSizerObservations->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	bSizerTopButtons = new wxBoxSizer( wxHORIZONTAL );


	m_fgSizerObservations->Add( bSizerTopButtons, 1, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( m_panelObservations, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_fgSizerObservations->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_ObservationsDateLabel1 = new wxStaticText( m_panelObservations, wxID_ANY, _("Current Vessel Data (date and time in UTC)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsDateLabel1->Wrap( -1 );
	bSizer6->Add( m_ObservationsDateLabel1, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizerObservationsLabels;
	fgSizerObservationsLabels = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizerObservationsLabels->SetFlexibleDirection( wxBOTH );
	fgSizerObservationsLabels->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_ObservationsDateLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Date"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsDateLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsDateLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsDate = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizerObservationsLabels->Add( m_ObservationsDate, 1, wxALL, 5 );

	m_ObservationsTimeLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Time"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsTimeLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsTimeLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsTime = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizerObservationsLabels->Add( m_ObservationsTime, 1, wxALL, 5 );

	m_ObservationsLatLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsLatLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsLatLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsLat = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizerObservationsLabels->Add( m_ObservationsLat, 1, wxALL, 5 );

	m_ObservationsLonLabel = new wxStaticText( m_panelObservations, wxID_ANY, _("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ObservationsLonLabel->Wrap( -1 );
	fgSizerObservationsLabels->Add( m_ObservationsLonLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_ObservationsLon = new wxTextCtrl( m_panelObservations, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizerObservationsLabels->Add( m_ObservationsLon, 1, wxALL, 5 );


	bSizer6->Add( fgSizerObservationsLabels, 1, wxEXPAND, 5 );


	m_fgSizerObservations->Add( bSizer6, 1, wxEXPAND, 5 );

	m_staticline11 = new wxStaticLine( m_panelObservations, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_fgSizerObservations->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* fgSizerObservationsButtons;
	fgSizerObservationsButtons = new wxFlexGridSizer( 1, 5, 0, 0 );
	fgSizerObservationsButtons->SetFlexibleDirection( wxBOTH );
	fgSizerObservationsButtons->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_ObservationsNew = new wxButton( m_panelObservations, wxID_ANY, _("New Row"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsNew, 0, wxALL, 5 );

	m_ObservationsDelete = new wxButton( m_panelObservations, wxID_ANY, _("Delete Row"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsDelete, 0, wxALL, 5 );

	m_ObservationsAddMarks = new wxButton( m_panelObservations, wxID_ANY, _("Add Marks"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsAddMarks, 0, wxALL, 5 );

	m_ObservationsDeleteMarks = new wxButton( m_panelObservations, wxID_ANY, _("Delete Marks"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsDeleteMarks, 0, wxALL, 5 );

	m_ObservationsExportObservations = new wxButton( m_panelObservations, wxID_ANY, _("Export CSV"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizerObservationsButtons->Add( m_ObservationsExportObservations, 0, wxALL, 5 );


	m_fgSizerObservations->Add( fgSizerObservationsButtons, 1, 0, 5 );


	m_panelObservations->SetSizer( m_fgSizerObservations );
	m_panelObservations->Layout();
	m_fgSizerObservations->Fit( m_panelObservations );
	m_notebookControl->AddPage( m_panelObservations, _("Observations"), true );

	fgSizer3->Add( m_notebookControl, 0, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* fgSizerBottomBar;
	fgSizerBottomBar = new wxFlexGridSizer( 1, 1, 0, 0 );
	fgSizerBottomBar->SetFlexibleDirection( wxBOTH );
	fgSizerBottomBar->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizerOKCancel;
	bSizerOKCancel = new wxBoxSizer( wxHORIZONTAL );

	m_buttonClose = new wxButton( this, wxID_ANY, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerOKCancel->Add( m_buttonClose, 0, wxALL, 5 );


	fgSizerBottomBar->Add( bSizerOKCancel, 1, wxEXPAND, 5 );


	fgSizer3->Add( fgSizerBottomBar, 1, wxEXPAND, 5 );


	m_SizerControl->Add( fgSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( m_SizerControl );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ooControlDialogDef::ooControlDialogDefOnClose ) );
	m_ObservationsNew->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickNewObservation ), NULL, this );
	m_ObservationsDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickDeleteObservation ), NULL, this );
	m_ObservationsAddMarks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsAddMarks ), NULL, this );
	m_ObservationsDeleteMarks->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsDeleteMarks ), NULL, this );
	m_ObservationsExportObservations->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickExportObservations ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::ooControlCloseClick ), NULL, this );

	return true;
}

ooControlDialogDef::~ooControlDialogDef()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ooControlDialogDef::ooControlDialogDefOnClose ) );
	m_ObservationsNew->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickNewObservation ), NULL, this );
	m_ObservationsDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickDeleteObservation ), NULL, this );
	m_ObservationsAddMarks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsAddMarks ), NULL, this );
	m_ObservationsDeleteMarks->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickObservationsDeleteMarks ), NULL, this );
	m_ObservationsExportObservations->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::OnButtonClickExportObservations ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooControlDialogDef::ooControlCloseClick ), NULL, this );

}
