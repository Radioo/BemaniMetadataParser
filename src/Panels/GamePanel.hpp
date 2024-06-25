//
// Created by Radio on 24/06/2024.
//

#ifndef BEMANIMETADATAPARSER_GAMEPANEL_HPP
#define BEMANIMETADATAPARSER_GAMEPANEL_HPP

#include <wx/wx.h>
#include <wx/grid.h>

#include "ChartManager.hpp"

class GamePanel : public wxPanel {
public:
    GamePanel(wxWindow* parent, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    wxGrid* gameGrid;

    void loadData();
    void openGameEditor(wxCommandEvent& event, Game* game);
};


#endif //BEMANIMETADATAPARSER_GAMEPANEL_HPP
