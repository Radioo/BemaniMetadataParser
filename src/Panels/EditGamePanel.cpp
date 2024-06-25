//
// Created by Radio on 24/06/2024.
//

#include "EditGamePanel.hpp"

EditGamePanel::EditGamePanel(wxWindow* parent, Game* game, ChartManager& chartManager) : wxPanel(parent), game(game), chartManager(chartManager) {
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto seriesSizer = new wxBoxSizer(wxHORIZONTAL);

    auto seriesLabel = new wxStaticText(this, wxID_ANY, wxT("Series"), wxDefaultPosition, wxDefaultSize, 0);
    seriesLabel->Wrap(-1);
    seriesSizer->Add(seriesLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    this->series = this->chartManager.getGameManager().getSeries();
    auto choices = wxArrayString();
    for(const auto& seriesItem : this->series) {
        choices.Add(seriesItem.name);
    }

    seriesChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices, 0);
    if(this->game != nullptr) {
        auto found = std::find_if(this->series.begin(), this->series.end(), [this](const Series& seriesItem) {
            return seriesItem.id == this->game->seriesId;
        });

        if(found != this->series.end()) {
            seriesChoice->SetSelection(static_cast<int>(std::distance(this->series.begin(), found)));
        }
        else {
            seriesChoice->SetSelection(0);
        }
    }
    else {
        seriesChoice->SetSelection(0);
    }
    seriesSizer->Add(seriesChoice, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(seriesSizer, 0, wxEXPAND, 5);

    wxBoxSizer* nameSizer;
    nameSizer = new wxBoxSizer(wxHORIZONTAL);

    auto nameLabel = new wxStaticText(this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
    nameLabel->Wrap(-1);
    nameSizer->Add(nameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    nameTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    if(this->game != nullptr) {
        nameTextCtrl->SetValue(wxString(this->game->name));
    }
    nameSizer->Add(nameTextCtrl, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(nameSizer, 0, wxEXPAND, 5);

    wxBoxSizer* versionSizer;
    versionSizer = new wxBoxSizer(wxHORIZONTAL);

    auto versionLabel = new wxStaticText(this, wxID_ANY, wxT("Version"), wxDefaultPosition, wxDefaultSize, 0);
    versionLabel->Wrap(-1);
    versionSizer->Add(versionLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    versionTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    if(this->game != nullptr) {
        versionTextCtrl->SetValue(wxString(std::to_string(this->game->version)));
    }
    versionSizer->Add(versionTextCtrl, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(versionSizer, 0, wxEXPAND, 5);

    auto saveButton = new wxButton(this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
    saveButton->Bind(wxEVT_BUTTON, &EditGamePanel::onSave, this);
    mainSizer->Add(saveButton, 0, wxALL | wxEXPAND, 5);


    this->SetSizer(mainSizer);
    this->Layout();
}

void EditGamePanel::onSave(wxCommandEvent& event) {
    auto gameManager = this->chartManager.getGameManager();
    auto selectedSeries = this->series[seriesChoice->GetSelection()];
    auto name = nameTextCtrl->GetValue().ToStdString();
    auto version = versionTextCtrl->GetValue().ToStdString();

    if(this->game == nullptr) {
        gameManager.addGame(selectedSeries.id, name, std::stoi(version));
    }
    else {
        this->game->seriesId = selectedSeries.id;
        this->game->name = name;
        this->game->version = std::stoi(version);
        gameManager.updateGame(*this->game);
    }

    this->GetParent()->Close();
}
