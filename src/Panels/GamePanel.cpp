//
// Created by Radio on 24/06/2024.
//

#include "GamePanel.hpp"
#include "EditGamePanel.hpp"
#include "../Helpers/UiHelper.hpp"

GamePanel::GamePanel(wxWindow* parent, ChartManager& chartManager) : wxPanel(parent), chartManager(chartManager) {
    wxBoxSizer* mainSizer;
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* headerSizer;
    headerSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* addGameButton = new wxButton(this, wxID_ANY, wxT("Add Game"), wxDefaultPosition, wxDefaultSize, 0);
    headerSizer->Add(addGameButton, 0, wxALL, 5);
    Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        this->openGameEditor(event, nullptr);
    }, addGameButton->GetId());

    mainSizer->Add(headerSizer, 0, wxEXPAND, 5);

    gameGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    UIHelper::setCommonGridAttributes(gameGrid);
    Bind(wxEVT_GRID_CELL_RIGHT_CLICK, [this](wxGridEvent& event) {
        auto gameId = std::stoi(UIHelper::getRowIdValue(gameGrid, event).ToStdString());

        auto* menu = UIHelper::getGridMenu();
        Bind(wxEVT_MENU, [this, &gameId](wxCommandEvent& event) {
            auto game = this->chartManager.getGameManager().getGame(gameId);
            this->openGameEditor(event, &game);
        }, wxID_EDIT);
        Bind(wxEVT_MENU, [this, &gameId](wxCommandEvent& event) {
            this->chartManager.getGameManager().deleteGame(gameId);
            this->loadData();
        }, wxID_DELETE);

        PopupMenu(menu);
    });

    mainSizer->Add(gameGrid, 1, wxALL | wxEXPAND, 5);

    this->SetSizer(mainSizer);
    this->Layout();

    loadData();
}

void GamePanel::loadData() {
    auto games = this->chartManager.getGameManager().getGames();
    auto count = static_cast<std::int32_t>(games.size());
    auto table = new wxGridStringTable(count, 4);

    table->SetColLabelValue(0, wxT("id"));
    table->SetColLabelValue(1, wxT("series_id"));
    table->SetColLabelValue(2, wxT("name"));
    table->SetColLabelValue(3, wxT("version"));

    for(std::int32_t i = 0; i < count; i++) {
        table->SetValue(i, 0, std::to_string(games[i].id));
        table->SetValue(i, 1, std::to_string(games[i].seriesId));
        table->SetValue(i, 2, games[i].name);
        table->SetValue(i, 3, std::to_string(games[i].version));
    }

    gameGrid->SetTable(table, true);
    gameGrid->AutoSizeColumns();
    gameGrid->AutoSizeRows();
}

void GamePanel::openGameEditor(wxCommandEvent& event, Game* game) {
    auto* dialog = new wxDialog(this, wxID_ANY, wxT("Edit Game"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    auto* panel = new EditGamePanel(dialog, game, this->chartManager);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND, 5);
    dialog->SetSizer(sizer);
    dialog->Fit();
    dialog->ShowModal();
    loadData();
}
