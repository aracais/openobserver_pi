/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  tpicons
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

#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "ocpn_plugin.h"

class tpicons
{
public:
    tpicons();
    ~tpicons();

    void    initialize_images(void);
    bool    ScaleIcons(void);
    bool    SetScaleFactor(void);
    void    SetColourScheme(PI_ColorScheme cs);
    void    ChangeScheme(void);

    wxBitmap    m_bm_openobserver_pi;
    wxBitmap    m_bm_openobserver_toggled_pi;
    wxBitmap    m_bm_openobserver_grey_pi;

    wxString    m_s_openobserver_pi;
    wxString    m_s_openobserver_toggled_pi;
    wxString    m_s_openobserver_grey_pi;

    bool        m_bUpdateIcons;

private:
    void        CreateSchemeIcons(void);
    wxBitmap    BuildDimmedToolBitmap(wxBitmap bmp_normal, unsigned char dim_ratio);

#ifdef PLUGIN_USE_SVG
    wxBitmap    LoadSVG( const wxString filename, unsigned int width = -1, unsigned int height = -1 );
#endif
    wxBitmap    m_bm_day_openobserver_pi;
    wxBitmap    m_bm_day_openobserver_toggled_pi;
    wxBitmap    m_bm_day_openobserver_grey_pi;

    wxBitmap    m_bm_dusk_openobserver_pi;
    wxBitmap    m_bm_dusk_openobserver_toggled_pi;
    wxBitmap    m_bm_dusk_openobserver_grey_pi;

    wxBitmap    m_bm_night_openobserver_pi;
    wxBitmap    m_bm_night_openobserver_toggled_pi;
    wxBitmap    m_bm_night_openobserver_grey_pi;

    double          m_dScaleFactor;
    PI_ColorScheme  m_ColourScheme;
    bool            m_failedBitmapLoad;

    int         m_iDisplayScaleFactor;
    int         m_iToolScaleFactor;
    int         m_iImageRefSize;
};
