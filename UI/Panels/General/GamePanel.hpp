//
// Created by Radio on 26/05/2024.
//

#ifndef BEMANIMETADATAPARSER_GAMEPANEL_HPP
#define BEMANIMETADATAPARSER_GAMEPANEL_HPP

#include <wx/grid.h>
#include <string>
#include "../BasePanel.hpp"

class GamePanel : public BasePanel {
public:
    explicit GamePanel(wxWindow* parent, Parser& parser);
    void afterCommit() override;
    void onPanelOpen() override;

private:
    wxStaticText* newGameErrorText;
    wxChoice* newGameSeriesSelect;
    wxButton* addNewGameButton;
    wxTextCtrl* newGameName;
    wxTextCtrl* newGameVersion;
    wxGrid* gameGrid;
    std::vector<std::tuple<std::uint32_t, std::string>> series;

    void refreshData();
    void onAddNewGame(wxCommandEvent& event);
};


#endif //BEMANIMETADATAPARSER_GAMEPANEL_HPP
