//
// Created by Radio on 24/06/2024.
//

#ifndef BEMANIMETADATAPARSER_EDITGAMEPANEL_HPP
#define BEMANIMETADATAPARSER_EDITGAMEPANEL_HPP

#include "ChartManager.hpp"

#include <wx/wx.h>

class EditGamePanel : public wxPanel{
public:
    EditGamePanel(wxWindow* parent, Game* game, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    Game* game;
    std::vector<Series> series;
    wxChoice* seriesChoice;
    wxTextCtrl* nameTextCtrl;
    wxTextCtrl* versionTextCtrl;

    void onSave(wxCommandEvent& event);
};


#endif //BEMANIMETADATAPARSER_EDITGAMEPANEL_HPP
