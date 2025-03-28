///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ooMiniDialogDef.h"

///////////////////////////////////////////////////////////////////////////

ooMiniDialogDef::ooMiniDialogDef()
{
}

ooMiniDialogDef::ooMiniDialogDef( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
{
	this->Create( parent, id, title, pos, size, style );
}

bool ooMiniDialogDef::Create( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
{
	if ( !wxDialog::Create( parent, id, title, pos, size, style ) )
	{
		return false;
	}

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_boxSizer = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* m_fgSizer;
	m_fgSizer = new wxFlexGridSizer( 2, 0, 0, 0 );
	m_fgSizer->AddGrowableCol( 0 );
	m_fgSizer->AddGrowableRow( 0 );
	m_fgSizer->SetFlexibleDirection( wxBOTH );
	m_fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_buttonOpenMainWindow = new wxButton( this, wxID_ANY, _("Open &Main Window"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fgSizer->Add( m_buttonOpenMainWindow, 0, wxALL, 5 );

	m_buttonClose = new wxButton( this, wxID_ANY, _("&Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fgSizer->Add( m_buttonClose, 0, wxALL, 5 );


	m_boxSizer->Add( m_fgSizer, 1, wxEXPAND, 5 );


	this->SetSizer( m_boxSizer );
	this->Layout();
	m_boxSizer->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonOpenMainWindow->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooMiniDialogDef::ooMiniOpenMainWindowClick ), NULL, this );
	m_buttonClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooMiniDialogDef::ooMiniCloseClick ), NULL, this );

	return true;
}

ooMiniDialogDef::~ooMiniDialogDef()
{
	// Disconnect Events
	m_buttonOpenMainWindow->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooMiniDialogDef::ooMiniOpenMainWindowClick ), NULL, this );
	m_buttonClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ooMiniDialogDef::ooMiniCloseClick ), NULL, this );

}
