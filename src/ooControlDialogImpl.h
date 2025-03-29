/***************************************************************************
* Project:  OpenCPN
* Purpose:  OpenObserver Plugin Control Dialog
* Author:   Jon Gough
*
* Project:  OpenCPN
*
***************************************************************************
*   Copyright (C) 2013 by David S. Register                               *
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

/**
 * @file
 * Subclass of ooControlDialogDef, which is generated by wxFormBuilder.
 */

#include <wx/grid.h>

#include "ooControlDialogDef.h"

#include "ooObservations.h"

///////////////////////////////////////////////////////////////////////////////
/// Class ooControlDialogImpl
///////////////////////////////////////////////////////////////////////////////
class ooControlDialogImpl : public ooControlDialogDef
{
public:
        ooControlDialogImpl(wxWindow *parent);
        ~ooControlDialogImpl();

        void CreateObservationsTable(ooObservations *table);

        void SetPositionFix(time_t fixTime, double lat, double lon);

protected:
        void ooControlStartStopObservationClick(wxCommandEvent& event);
        void ooControlOpenMiniWindowClick(wxCommandEvent& event);

        void OnButtonClickNewObservation( wxCommandEvent& event );
        void OnButtonClickDeleteObservation( wxCommandEvent& event );
        void OnButtonClickExportObservations( wxCommandEvent& event );
        void OnButtonClickObservationsAddMarks( wxCommandEvent& event );
        void OnButtonClickObservationsDeleteMarks( wxCommandEvent& event );

        void ooControlCloseClick(wxCommandEvent& event);

private:
        void OnBackupTimer(wxTimerEvent& event);
        void OnObservationDurationTimer(wxTimerEvent& event);

        void save_observations_to_csv(wxFile *file);
        void save_observations_to_xml(wxFile *file);
        void read_observations_from_xml(wxString& filename);

        wxString m_BackupFilename;
        wxTimer m_BackupTimer;

        wxTimer m_ObservationDurationTimer;
        wxStopWatch m_ObservationDurationStopWatch;

        wxGrid* m_ObservationsTable;
};
