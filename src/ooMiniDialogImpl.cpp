/**************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  OpenObserver Plugin Mini Dialog
 * Author:   Alex Mansfield
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

#include "ooMiniDialogImpl.h"
#include "openobserver_pi.h"


extern openobserver_pi *g_openobserver_pi;

ooMiniDialogImpl::ooMiniDialogImpl(wxWindow* parent) : ooMiniDialogDef(parent)
{
#if wxCHECK_VERSION(3,0,0)
    SetLayoutAdaptationMode(wxDIALOG_ADAPTATION_MODE_ENABLED);
#endif // wxCHECK_VERSION(3,0,0)
}

ooMiniDialogImpl::~ooMiniDialogImpl()
{
}

void ooMiniDialogImpl::ooMiniOpenMainWindowClick(wxCommandEvent& event)
{
    g_openobserver_pi->ToggleWindow();
}

void ooMiniDialogImpl::ooMiniCloseClick(wxCommandEvent& event)
{
    g_openobserver_pi->ToggleToolbarIcon();
}


