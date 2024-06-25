//
// Created by Radio on 25/06/2024.
//

#ifndef BEMANIMETADATAPARSER_RELEASEPANEL_HPP
#define BEMANIMETADATAPARSER_RELEASEPANEL_HPP

#include <wx/wx.h>
#include <wx/grid.h>

#include "ChartManager.hpp"

class ReleasePanel : public wxPanel {
public:
    ReleasePanel(wxWindow* parent, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    wxGrid* releaseGrid;

    void loadData();
    void openReleaseEditor(wxCommandEvent& event, Release* release);
};


#endif //BEMANIMETADATAPARSER_RELEASEPANEL_HPP
