//
// Created by Radio on 20/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SERIESPANEL_HPP
#define BEMANIMETADATAPARSER_SERIESPANEL_HPP

#include <wx/wx.h>
#include <wx/grid.h>

#include "ChartManager.hpp"

class SeriesPanel : public wxPanel {
public:
    SeriesPanel(wxWindow* parent, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    wxGrid* seriesGrid;

    void loadData();
    void openSeriesEditor(wxCommandEvent& event, Series* series);
};


#endif //BEMANIMETADATAPARSER_SERIESPANEL_HPP
