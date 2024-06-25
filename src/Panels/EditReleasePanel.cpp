//
// Created by Radio on 25/06/2024.
//

#include "EditReleasePanel.hpp"

EditReleasePanel::EditReleasePanel(wxWindow* parent, Release* release, ChartManager& chartManager) : wxPanel(parent), chartManager(chartManager), release(release) {
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto gameSizer = new wxBoxSizer(wxHORIZONTAL);

    auto gameLabel = new wxStaticText(this, wxID_ANY, wxT("Game"), wxDefaultPosition, wxDefaultSize, 0);
    gameLabel->Wrap(-1);
    gameSizer->Add(gameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto choices = wxArrayString();
    this->games = this->chartManager.getGameManager().getGames();
    if(this->games.empty()) {
        throw std::runtime_error("No games found");
    }
    for(const auto& game: this->games) {
        choices.Add(game.name);
    }
    gameChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices, 0);
    if(this->release != nullptr) {
        auto found = std::find_if(games.begin(), games.end(), [this](const Game& game) {
            return game.id == this->release->gameId;
        });

        if(found != games.end()) {
            gameChoice->SetSelection(static_cast<int>(std::distance(games.begin(), found)));
        } else {
            gameChoice->SetSelection(0);
        }
    } else {
        gameChoice->SetSelection(0);
    }
    gameSizer->Add(gameChoice, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(gameSizer, 0, wxEXPAND, 5);

    auto codeSizer = new wxBoxSizer(wxHORIZONTAL);

    auto codeLabel = new wxStaticText(this, wxID_ANY, wxT("Code"), wxDefaultPosition, wxDefaultSize, 0);
    codeLabel->Wrap(-1);
    codeSizer->Add(codeLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    codeTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    if(this->release != nullptr) {
        codeTextCtrl->SetValue(wxString(this->release->code));
    }
    codeSizer->Add(codeTextCtrl, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    mainSizer->Add(codeSizer, 0, wxEXPAND, 5);

    auto saveButton = new wxButton(this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
    saveButton->Bind(wxEVT_BUTTON, &EditReleasePanel::onSave, this);
    mainSizer->Add(saveButton, 0, wxALL | wxEXPAND, 5);


    this->SetSizer(mainSizer);
    this->Layout();
}

void EditReleasePanel::onSave(wxCommandEvent& event) {
    auto gameManager = this->chartManager.getGameManager();
    auto selectedGame = games[gameChoice->GetSelection()];
    auto code = codeTextCtrl->GetValue().ToStdString();

    if(this->release != nullptr) {
        this->release->gameId = selectedGame.id;
        this->release->code = code;
        gameManager.updateRelease(*this->release);
    }
    else {
        gameManager.addRelease(selectedGame.id, code);
    }

    this->GetParent()->Close();
}
