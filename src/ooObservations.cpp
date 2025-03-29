/**************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  OpenObserver Plugin Observations
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

#include "ooObservations.h"

ooObservations::ooObservations() : wxGridStringTable(0, 7)
{
    SetColLabelValue( 0, _("Date") );
	SetColLabelValue( 1, _("Time (UTC)") );
	SetColLabelValue( 2, _("Lat") );
	SetColLabelValue( 3, _("Lon") );
	SetColLabelValue( 4, _("Species") );
	SetColLabelValue( 5, _("Notes") );
	SetColLabelValue( 6, _("Mark GUID") );

    wxArrayInt allColSizes;
    allColSizes.Add(70);
    allColSizes.Add(70);
    allColSizes.Add(90);
    allColSizes.Add(90);
    allColSizes.Add(100);
    allColSizes.Add(200);
    allColSizes.Add(70);

    m_col_sizes = wxGridSizesInfo(70, allColSizes);
}

ooObservations::~ooObservations()
{
}

wxGridSizesInfo ooObservations::GetColSizes() const
{
    return m_col_sizes;
}