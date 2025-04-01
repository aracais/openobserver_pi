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

#include <wx/log.h>
#include <wx/sstream.h>
#include <wx/xml/xml.h>

#include "ocpn_plugin.h"

ooObservations::ooObservations() : wxGridStringTable(0, 7), m_IsObserving(false)
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

    m_col_field_types.Clear();
    m_col_field_types.Add("Start Date");
    m_col_field_types.Add("Start Time");
    m_col_field_types.Add("Start Latitude");
    m_col_field_types.Add("Start Longitude");
    m_col_field_types.Add("Text");
    m_col_field_types.Add("Text");
    m_col_field_types.Add("Mark GUID");
}

ooObservations::~ooObservations()
{
}

wxGridSizesInfo ooObservations::GetColSizes() const
{
    return m_col_sizes;
}

void ooObservations::SetColSizes(const wxGridSizesInfo &sizeInfo)
{
    m_col_sizes = sizeInfo;
}

wxArrayString ooObservations::GetColFieldTypes() const
{
    return m_col_field_types;
}

void ooObservations::SetColFieldTypes(const wxArrayString &colFieldTypes)
{
    m_col_field_types = colFieldTypes;
}

void ooObservations::SetPositionFix(time_t fixTime, double lat, double lon)
{
    m_position_fix_time = fixTime;
    m_position_fix_lat = lat;
    m_position_fix_lon = lon;
}

void ooObservations::StartObservation()
{
    if (m_IsObserving) return;

    // start duration stopwatch
    m_ObservationDurationStopWatch.Start(0);

    // get date and time
    char dateString[16];
    std::strftime(dateString, 16, "%F", gmtime(&m_position_fix_time));
    char timeString[16];
    std::strftime(timeString, 16, "%T", gmtime(&m_position_fix_time));

    // create new observation in table and fill in fields
    InsertRows(0, 1);
    const int C = GetNumberCols();
    if (m_col_field_types.GetCount() == C)
    {
        for (int c=0; c<C; ++c)
        {
            wxString field_type = m_col_field_types[c];
            if (field_type.IsSameAs("Start Date"))
                SetValue(0, c, dateString);
            else if (field_type.IsSameAs("Start Time"))
                SetValue(0, c, timeString);
            else if (field_type.IsSameAs("Start Latitude"))
                SetValue(0, c, toSDMM_PlugIn(1, m_position_fix_lat));
            else if (field_type.IsSameAs("Start Longitude"))
                SetValue(0, c, toSDMM_PlugIn(2, m_position_fix_lon));
        }
    } else {
        wxLogError("m_col_field_types.GetCount() does not match number of observation columns");
    }

    m_IsObserving = true;
}

void ooObservations::StopObservation()
{
    if (!m_IsObserving) return;

    m_ObservationDurationStopWatch.Pause();

    // get date and time
    char dateString[16];
    std::strftime(dateString, 16, "%F", gmtime(&m_position_fix_time));
    char timeString[16];
    std::strftime(timeString, 16, "%T", gmtime(&m_position_fix_time));

    // fill in fields
    const int C = GetNumberCols();
    if (m_col_field_types.GetCount() == C)
    {
        for (int c=0; c<C; ++c)
        {
            wxString field_type = m_col_field_types[c];
            if (field_type.IsSameAs("End Date"))
                SetValue(0, c, dateString);
            else if (field_type.IsSameAs("End Time"))
                SetValue(0, c, timeString);
            else if (field_type.IsSameAs("End Latitude"))
                SetValue(0, c, toSDMM_PlugIn(1, m_position_fix_lat));
            else if (field_type.IsSameAs("End Longitude"))
                SetValue(0, c, toSDMM_PlugIn(2, m_position_fix_lon));
            else if (field_type.IsSameAs("Observation Duration"))
                SetValue(0, c, wxString::Format(wxT("%li"), m_ObservationDurationStopWatch.Time()));
        }
    } else {
        wxLogError("m_col_field_types.GetCount() does not match number of observation columns");
    }

    m_IsObserving = false;
}

bool ooObservations::IsObserving() const
{
    return m_IsObserving;
}

long ooObservations::GetObservationDuration()
{
    return m_ObservationDurationStopWatch.Time();
}

void ooObservations::AddMarks()
{
    // Get column indices
    int markGUIDCol = -1;
    int dateCol = -1;
    int timeCol = -1;
    int latCol = -1;
    int lonCol = -1;
    int nameCol = -1;
    int descriptionCol = -1;
    
    const int C = GetNumberCols();
    if (m_col_field_types.GetCount() == C)
    {
        for (int c=0; c<C; ++c)
        {
            wxString field_type = m_col_field_types[c];
            if (field_type.IsSameAs("Mark GUID")) {
                if (markGUIDCol < 0) markGUIDCol = c;
            } else if (field_type.IsSameAs("Start Date")) {
                if (dateCol < 0) dateCol = c;
            } else if (field_type.IsSameAs("Start Time")) {
                if (timeCol < 0) timeCol = c;
            } else if (field_type.IsSameAs("Start Latitude")) {
                if (latCol < 0) latCol = c;
            } else if (field_type.IsSameAs("Start Longitude")) {
                if (lonCol < 0) lonCol = c;
            } else if (field_type.IsSameAs("Text")) {
                // use first text column as name and second as description
                if (nameCol < 0) nameCol = c;
                else if (descriptionCol < 0) descriptionCol = c;
            }
        }
    } else {
        wxLogError("m_col_field_types.GetCount() does not match number of observation columns");
        return;
    }

    if (markGUIDCol < 0) {
        wxLogError("Could not find a column for storing the Mark GUID");
        return;
    }

    if ((latCol < 0) || (lonCol < 0)) {
        wxLogError("Could not find columns storing the latitude and longitude, so unable to make marks");
        return;
    }

    const int R = GetNumberRows();
    for (int r=0; r<R; ++r)
    {
        if (GetValue(r, markGUIDCol).IsEmpty())
        {
            const double lat = fromDMM_Plugin(GetValue(r, latCol));
            const double lon = fromDMM_Plugin(GetValue(r, lonCol));

            wxDateTime datetime;
            if (dateCol>=0) datetime.ParseISODate(GetValue(r, dateCol));
            if (timeCol>=0) datetime.ParseISOTime(GetValue(r, timeCol));

            wxString name = (nameCol>=0) ? GetValue(r, nameCol) + " (OO)" : "Mark (OO)";
            wxString description = (descriptionCol>=0) ? GetValue(r, descriptionCol) : "";

            wxString guid = GetNewGUID();

            // add waypoint
            PlugIn_Waypoint wp(lat, lon, "fish", name, guid);
            wp.m_MarkDescription = description;
            wp.m_CreateTime = datetime;
            AddSingleWaypoint(&wp);

            // store guid in table
            SetValue(r, markGUIDCol, guid);
        }
    }
}

void ooObservations::DeleteMarks()
{
    // Get column indices
    int markGUIDCol = -1;
    
    const int C = GetNumberCols();
    if (m_col_field_types.GetCount() == C)
    {
        for (int c=0; c<C; ++c)
        {
            wxString field_type = m_col_field_types[c];
            if (field_type.IsSameAs("Mark GUID")) {
                if (markGUIDCol < 0) markGUIDCol = c;
            }
        }
    } else {
        wxLogError("m_col_field_types.GetCount() does not match number of observation columns");
        return;
    }

    if (markGUIDCol < 0) {
        wxLogError("Could not find a column for storing the Mark GUID");
        return;
    }

    const int R = GetNumberRows();
    for (int r=0; r<R; ++r)
    {
        wxString guid = GetValue(r, markGUIDCol);
        if (guid.IsEmpty()) continue;

        // delete waypoint
        DeleteSingleWaypoint(guid);

        // remove guid from table
        guid.Clear();
        SetValue(r, markGUIDCol, guid);
    }
}

void ooObservations::SaveToCSV(wxFile *file)
{
    const int C = GetNumberCols();
    const int R = GetNumberRows();
    
    for (int c=0; c<C; ++c)
    {
        file->Write("\"" + GetColLabelValue(c) + "\"");

        if (c<(C - 1))
            file->Write(",");
    }
    file->Write("\n");

    for (int r=0; r<R; ++r)
    {
        for (int c=0; c<C; ++c)
        {
            file->Write("\"" + GetValue(r, c) + "\"");

            if (c<(C - 1))
                file->Write(",");
        }
        file->Write("\n");
    }

    file->Close();
}

void ooObservations::SaveToXML(wxFile *file)
{
    const int C = GetNumberCols();
    const int R = GetNumberRows();

    wxXmlDocument xmlDoc;    
    wxXmlNode* observations = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "observations");
    observations->AddAttribute("creator", "OpenObserver for OpenCPN");
    xmlDoc.SetRoot(observations);
    
    for (int r=0; r<R; ++r) {
        wxXmlNode* observation = new wxXmlNode (observations, wxXML_ELEMENT_NODE, "observation");
        observation->AddAttribute("id", wxString::Format(wxT("%i"), r));

        for (int c=0; c<C; ++c) {
            wxXmlNode* field = new wxXmlNode(observation, wxXML_ELEMENT_NODE, "field");
            field->AddAttribute("id", wxString::Format(wxT("%i"), c));
            field->AddChild(new wxXmlNode(wxXML_TEXT_NODE, "",  GetValue(r, c)));
        }
    }
    
    // write the output to a wxString
    wxStringOutputStream stream;
    xmlDoc.Save(stream);

    // write the string to the file
    file->Write(stream.GetString());    
}

bool ooObservations::ReadFromXML(wxString& filename)
{
    wxXmlDocument xmlDoc;
    if ((!xmlDoc.Load(filename)) || (xmlDoc.GetRoot()->GetName() != "observations")) {
        return false;
    }

    const int C = GetNumberCols();
    wxXmlNode *observation = xmlDoc.GetRoot()->GetChildren();
    while (observation)
    {
        int r = -1;
        if (observation->GetAttribute("id").ToInt(&r) && (r>=0)) {

            // expand number of rows as needed to accommodate observations
            if (r >= GetNumberRows()) {
                AppendRows(r - GetNumberRows() + 1);
            }

            wxXmlNode *field = observation->GetChildren();
            while (field) {
                if (field->GetChildren()) {
                    int c = -1;
                    if (field->GetAttribute("id").ToInt(&c) && (c>=0) && (c<C)) {
                        SetValue(r, c, field->GetChildren()->GetContent());
                    }
                }

                field = field->GetNext();
            }
        }

        observation = observation->GetNext();
    }

    return true;
}

wxArrayString ooObservations::GetObservationFieldTypes()
{
    wxArrayString observationFieldTypes;
    observationFieldTypes.Add("Start Date");
    observationFieldTypes.Add("Start Time");
    observationFieldTypes.Add("Start Latitude");
    observationFieldTypes.Add("Start Longitude");
    observationFieldTypes.Add("End Date");
    observationFieldTypes.Add("End Time");
    observationFieldTypes.Add("End Latitude");
    observationFieldTypes.Add("End Longitude");
    observationFieldTypes.Add("Observation Duration");
    observationFieldTypes.Add("Mark GUID");
    observationFieldTypes.Add("Text");
    return observationFieldTypes;
}