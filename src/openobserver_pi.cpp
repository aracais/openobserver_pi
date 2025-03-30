/******************************************************************************
 * updated: 4-5-2012
 * Project:  OpenCPN
 * Purpose:  OpenObserver Plugin
 * Author:   Jon Gough
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
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
 ***************************************************************************
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers
#include <wx/stdpaths.h>
#include <wx/timer.h>
#include <wx/event.h>
#include <wx/sysopt.h>
#include <wx/dir.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>
#include <wx/msgdlg.h>
#include <wx/listbook.h>
#include <wx/panel.h>
#include <wx/ffile.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

#include <wx/aui/aui.h>

#include "openobserver_pi.h"
#include "version.h"
#include "wxWTranslateCatalog.h"

#include "tpicons.h"
#include "ooObservations.h"
#include "ooControlDialogImpl.h"
#include "ooMiniDialogImpl.h"

#include "wx/jsonwriter.h"


#ifndef DECL_EXP
#ifdef __WXMSW__
#define DECL_EXP     __declspec(dllexport)
#else
#define DECL_EXP
#endif
#endif

#if !defined(NAN)
static const long long lNaN = 0xfff8000000000000;
#define NAN (*(double*)&lNaN)
#endif

openobserver_pi         *g_openobserver_pi;
wxString                *g_PrivateDataDir;

wxString                *g_pData;
wxString                *g_SData_Locn;
wxString                *g_pLayerDir;

wxString                *g_tplocale;
void                    *g_ppimgr;

int                     g_iLocaleDepth;

wxFont                  *g_pFontTitle;
wxFont                  *g_pFontData;
wxFont                  *g_pFontLabel;
wxFont                  *g_pFontSmall;

// Needed for ocpndc.cpp to compile. Normally would be in glChartCanvas.cpp
float g_GLMinSymbolLineWidth;

void appendOSDirSlash(wxString* pString)
{
    wxChar sep = wxFileName::GetPathSeparator();

    if (pString->Last() != sep)
        pString->Append(sep);
}

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new openobserver_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}


//---------------------------------------------------------------------------------------------------------
//
//    openobserver PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

openobserver_pi::openobserver_pi(void *ppimgr) : opencpn_plugin_118(ppimgr), m_ooObservations(nullptr)
{
    // Create the PlugIn icons
    g_ppimgr = ppimgr;
    g_openobserver_pi = this;

    wxString *l_pDir = new wxString(*GetpPrivateApplicationDataLocation());
    appendOSDirSlash(l_pDir);

    l_pDir->Append(_T("plugins"));
    appendOSDirSlash(l_pDir);
    if (!wxDir::Exists(*l_pDir))
        wxMkdir(*l_pDir);

    g_PrivateDataDir = new wxString(*l_pDir);
    g_PrivateDataDir->Append(_T("openobserver_pi"));
    appendOSDirSlash(g_PrivateDataDir);
    if (!wxDir::Exists(*g_PrivateDataDir))
        wxMkdir(*g_PrivateDataDir);

    g_pData = new wxString(*g_PrivateDataDir);
    g_pData->append(wxS("data"));
    appendOSDirSlash(g_pData);
    if (!wxDir::Exists(*g_pData))
        wxMkdir(*g_pData);

    g_pLayerDir = new wxString(*g_PrivateDataDir);
    g_pLayerDir->Append(wxT("Layers"));
    appendOSDirSlash(g_pLayerDir);
    if (!wxDir::Exists(*g_pLayerDir))
        wxMkdir(*g_pLayerDir);

    m_ptpicons = new tpicons();

    delete l_pDir;
}

openobserver_pi::~openobserver_pi()
{
    delete g_SData_Locn;
    g_SData_Locn = NULL;

    delete g_PrivateDataDir;
    g_PrivateDataDir = NULL;

    delete g_pData;
    g_pData = NULL;

    delete g_pLayerDir;
    g_pLayerDir = NULL;
}

int openobserver_pi::Init(void)
{
    g_tplocale = nullptr;
    m_bReadyForRequests = false;
    m_bShowMainDialog = true;
    m_ooControlDialogImpl = nullptr;
    m_ooMiniDialogImpl = nullptr;
    m_cursor_lat = 0.0;
    m_cursor_lon = 0.0;
    m_click_lat = 0.0;
    m_click_lon = 0.0;

    // Adds local language support for the plugin to OCPN
    AddLocaleCatalog(PLUGIN_CATALOG_NAME);

    // Get a pointer to the opencpn display canvas, to use as a parent for windows created
    m_parent_window = GetOCPNCanvasWindow();
    m_pConfig = GetOCPNConfigObject();

    m_ooObservations = new ooObservations();

    m_ooControlDialogImpl = new ooControlDialogImpl(m_parent_window);
    m_ooControlDialogImpl->CreateObservationsTable(m_ooObservations);
    m_ooControlDialogImpl->Fit();
    m_ooControlDialogImpl->Layout();
    m_ooControlDialogImpl->Hide();

    m_ooMiniDialogImpl = new ooMiniDialogImpl(m_parent_window);
    m_ooMiniDialogImpl->Fit();
    m_ooMiniDialogImpl->Layout();
    m_ooMiniDialogImpl->Hide();

    LoadConfig();

#ifdef PLUGIN_USE_SVG
    m_openobserver_button_id  = InsertPlugInToolSVG(_("OpenObserver Plugin"), m_ptpicons->m_s_openobserver_grey_pi, m_ptpicons->m_s_openobserver_pi, m_ptpicons->m_s_openobserver_toggled_pi, wxITEM_CHECK,
                                                  _("OpenObserver Plugin"), wxS(""), NULL, openobserver_POSITION, 0, this);
#else
    m_openobserver_button_id  = InsertPlugInTool(_("OpenObserver Plugin"), &m_ptpicons->m_bm_openobserver_grey_pi, &m_ptpicons->m_bm_openobserver_pi, wxITEM_CHECK,
                                             _("OpenObserver Plugin"), wxS(""), NULL, openobserver_POSITION, 0, this);
#endif

    //    In order to avoid an ASSERT on msw debug builds,
    //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
    //    The Items will be re-parented when added to the real context meenu
    wxMenu dummy_menu;

    // Get item into font list in options/user interface
    AddPersistentFontKey( wxT("tp_Label") );
    AddPersistentFontKey( wxT("tp_Data") );
    g_pFontTitle = GetOCPNScaledFont_PlugIn( wxS("tp_Title") );
    g_pFontLabel = GetOCPNScaledFont_PlugIn( wxS("tp_Label") );
    g_pFontData = GetOCPNScaledFont_PlugIn( wxS("tp_Data") );
    g_pFontSmall = GetOCPNScaledFont_PlugIn( wxS("tp_Small") );
    wxColour l_fontcolour = GetFontColour_PlugIn( wxS("tp_Label") );
    l_fontcolour = GetFontColour_PlugIn( wxS("tp_Data") );

    return (
        WANTS_CURSOR_LATLON       |
        WANTS_TOOLBAR_CALLBACK    |
        INSTALLS_TOOLBAR_TOOL     |
//        WANTS_CONFIG              |
        INSTALLS_TOOLBOX_PAGE     |
        INSTALLS_CONTEXTMENU_ITEMS  |
        WANTS_NMEA_EVENTS         |
//        WANTS_NMEA_SENTENCES        |
        //    USES_AUI_MANAGER            |
//        WANTS_PREFERENCES         |
        //    WANTS_ONPAINT_VIEWPORT      |
        WANTS_PLUGIN_MESSAGING    |
        WANTS_LATE_INIT           |
        WANTS_MOUSE_EVENTS        |
        WANTS_KEYBOARD_EVENTS
    );
}

void openobserver_pi::LateInit(void)
{
    SendPluginMessage(wxS("OPENOBSERVER_PI_READY_FOR_REQUESTS"), wxS("TRUE"));
    m_bReadyForRequests = true;
    return;
}

bool openobserver_pi::DeInit(void)
{
    if (m_ooControlDialogImpl)
    {
        m_ooControlDialogImpl->Close();
        delete m_ooControlDialogImpl;
        m_ooControlDialogImpl = nullptr;
    }
    if (m_ooMiniDialogImpl)
    {
        m_ooMiniDialogImpl->Close();
        delete m_ooMiniDialogImpl;
        m_ooMiniDialogImpl = nullptr;
    }
    if (m_pConfig) SaveConfig();

    return true;
}

int openobserver_pi::GetAPIVersionMajor()
{
      return OCPN_API_VERSION_MAJOR;
}

int openobserver_pi::GetAPIVersionMinor()
{
      return OCPN_API_VERSION_MINOR;
}

int openobserver_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int openobserver_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

int openobserver_pi::GetPlugInVersionPatch()
{
    return PLUGIN_VERSION_PATCH;
}

int openobserver_pi::GetPlugInVersionPost()
{
    return PLUGIN_VERSION_TWEAK;
}

wxString openobserver_pi::GetCommonName()
{
    return _T(PLUGIN_COMMON_NAME);
}

wxString openobserver_pi::GetShortDescription()
{
    return _(PLUGIN_SHORT_DESCRIPTION);
}

wxString openobserver_pi::GetLongDescription()
{
    return _(PLUGIN_LONG_DESCRIPTION);
}

int openobserver_pi::GetToolbarToolCount(void)
{
      return 1;
}

void openobserver_pi::OnToolbarToolCallback(int id)
{
    m_iCallerId = id;
    ToggleToolbarIcon();
}

void openobserver_pi::OnToolbarToolDownCallback(int id)
{
    return;
}

void openobserver_pi::OnToolbarToolUpCallback(int id)
{
    m_ptpicons->SetScaleFactor();
    return;
}

bool openobserver_pi::KeyboardEventHook( wxKeyEvent &event )
{
    bool bret = false;

    if( event.GetKeyCode() < 128 ) // ASCII
    {
        int key_char = event.GetKeyCode();

        if ( event.ControlDown() )
            key_char -= 64;

        switch( key_char ) {
            case WXK_CONTROL_W: // Ctrl W
                if ( event.ShiftDown() ) { // Shift-Ctrl-W
                    if(event.GetEventType() == wxEVT_KEY_DOWN) {
                        OnToolbarToolDownCallback( m_openobserver_button_id);
                    }
                    bret = true;
                } else bret = false;
                break;
        }
    }
    if(bret) RequestRefresh(m_parent_window);
    return bret;
}

bool openobserver_pi::MouseEventHook( wxMouseEvent &event )
{
    if (event.LeftDown()) {
        m_click_lat = m_cursor_lat;
        m_click_lon = m_cursor_lon;
    }

    return false;
}

void openobserver_pi::SetCursorLatLon(double lat, double lon)
{
    m_cursor_lat = lat;
    m_cursor_lon = lon;
}

void openobserver_pi::SetPositionFix(PlugIn_Position_Fix &pfix)
{
    if (m_ooObservations)
        m_ooObservations->SetPositionFix(pfix.FixTime, pfix.Lat, pfix.Lon);
    if (m_ooControlDialogImpl)
        m_ooControlDialogImpl->SetPositionFix(pfix.FixTime, pfix.Lat, pfix.Lon);
}

wxBitmap *openobserver_pi::GetPlugInBitmap()
{
    return &m_ptpicons->m_bm_openobserver_pi;
}

void openobserver_pi::ToggleToolbarIcon()
{
    if (!m_ooControlDialogImpl || !m_ooMiniDialogImpl) return;

    if (m_ooControlDialogImpl->IsShown() || m_ooMiniDialogImpl->IsShown()) {
        SetToolbarItemState(m_openobserver_button_id, false);
        m_ooControlDialogImpl->Hide();
        m_ooMiniDialogImpl->Hide();
    } else {
        SetToolbarItemState(m_openobserver_button_id, true);
        if (m_bShowMainDialog) {
            m_ooMiniDialogImpl->Hide();
            m_ooControlDialogImpl->Show();
        } else {
            m_ooControlDialogImpl->Hide();
            m_ooMiniDialogImpl->Show();
        }
    }
}

void openobserver_pi::ToggleWindow()
{
    if (!m_ooControlDialogImpl || !m_ooMiniDialogImpl) return;

    if (m_ooControlDialogImpl->IsShown()) {
        m_ooControlDialogImpl->Hide();
        m_ooMiniDialogImpl->Show();
        m_bShowMainDialog = false;
    } else {
        m_ooMiniDialogImpl->Hide();
        m_ooControlDialogImpl->Show();
        m_bShowMainDialog = true;
    }
}

void openobserver_pi::SaveConfig()
{
    #ifndef __WXMSW__
    wxSetlocale(LC_NUMERIC, NULL);
    #if wxCHECK_VERSION(3,0,0)  && !defined(_WXMSW_)
    //#if wxCHECK_VERSION(3,0,0)
    wxSetlocale(LC_NUMERIC, "C");
    #else
    setlocale(LC_NUMERIC, "C");
    #endif
    #endif

    if(m_pConfig) 
    {
        // section in the main OpenCPN setting file (Mac ~/Library/preferences/opencpn/opencpn.ini)
        m_pConfig->SetPath( wxS( "/Settings/openobserver_pi" ) );
        // if(m_bRecreateConfig) {
        //     m_pConfig->DeleteGroup( "/Settings/openobserver_pi" );
        // } else {
        //     m_pConfig->Write( wxS( "SaveJSONOnStartup" ), g_bSaveJSONOnStartup );
        //     m_pConfig->Write( wxS( "JSONSaveFile" ), m_fnOutputJSON.GetFullPath());
        //     m_pConfig->Write( wxS( "JSONInputFile" ), m_fnInputJSON.GetFullPath());
        //     m_pConfig->Write( wxS( "CloseSaveFileAferEachWrite" ), m_bCloseSaveFileAfterEachWrite);
        //     m_pConfig->Write( wxS( "AppendToSaveFile" ), m_bAppendToSaveFile);
        //     m_pConfig->Write( wxS( "SaveIncommingJSONMessages" ), m_bSaveIncommingJSONMessages);
        // }
    }
}

void openobserver_pi::LoadConfig()
{
    #ifndef __WXMSW__
    wxSetlocale(LC_NUMERIC, NULL);
    #if wxCHECK_VERSION(3,0,0)
    wxSetlocale(LC_NUMERIC, "C");
    #else
    setlocale(LC_NUMERIC, "C");
    #endif
    #endif

    if(m_pConfig)
    {
        m_pConfig->SetPath( wxS( "/Settings/openobserver_pi" ) );
        // m_pConfig->Read( wxS( "SaveJSONOnStartup"), &g_bSaveJSONOnStartup, false );
        // if(g_bSaveJSONOnStartup) m_ooControlDialogImpl->SetSaveJSONOnStartup(g_bSaveJSONOnStartup);
        // wxString l_filepath;
        // m_pConfig->Read( wxS("JSONSaveFile"), &l_filepath, wxEmptyString);
        // m_fnOutputJSON.Assign(l_filepath);
        // if(m_fnOutputJSON != wxEmptyString) m_ooControlDialogImpl->SetJSONSaveFile(m_fnOutputJSON.GetFullPath());
        // m_pConfig->Read( wxS( "JSONInputFile" ), &l_filepath, wxEmptyString);
        // m_fnInputJSON.Assign(l_filepath);
        // if(m_fnInputJSON != wxEmptyString) m_ooControlDialogImpl->SetJSONInputFile(m_fnInputJSON.GetFullPath());
        // m_pConfig->Read( wxS( "CloseSaveFileAferEachWrite" ), &m_bCloseSaveFileAfterEachWrite, true);
        // m_ooControlDialogImpl->SetCloseFileAfterEachWrite(m_bCloseSaveFileAfterEachWrite);
        // m_pConfig->Read( wxS( "AppendToSaveFile" ), &m_bAppendToSaveFile, true);
        // m_ooControlDialogImpl->SetAppendToSaveFile(m_bAppendToSaveFile);
        // m_pConfig->Read( wxS( "SaveIncommingJSONMessages" ), &m_bSaveIncommingJSONMessages, false);
        // m_ooControlDialogImpl->SetIncommingJSONMessages(m_bSaveIncommingJSONMessages);
    }
}
