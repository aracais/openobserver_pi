///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

#include "wxWTranslateCatalog.h"

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class ooMiniDialogDef
///////////////////////////////////////////////////////////////////////////////
class ooMiniDialogDef : public wxDialog
{
	private:

	protected:
		wxBoxSizer* m_boxSizer;
		wxButton* m_buttonOpenMainWindow;

		// Virtual event handlers, override them in your derived class
		virtual void ooMiniDialogDefOnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void ooMiniOpenMainWindowClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		ooMiniDialogDef();
		ooMiniDialogDef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("OpenObserver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
		bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("OpenObserver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );

		~ooMiniDialogDef();

};

