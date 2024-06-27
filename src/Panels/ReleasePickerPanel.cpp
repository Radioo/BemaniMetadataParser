//
// Created by Radio on 25/06/2024.
//

#include "ReleasePickerPanel.hpp"

ReleasePickerPanel::ReleasePickerPanel(wxWindow* parent, ChartManager& chartManager, std::optional<ReleaseInfo>& releaseInfo) : wxPanel(parent), chartManager(chartManager), releaseInfo(releaseInfo) {
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto seriesSizer = new wxBoxSizer(wxHORIZONTAL);

    auto seriesLabel = new wxStaticText(this, wxID_ANY, wxT("Series"), wxDefaultPosition, wxDefaultSize, 0);
    seriesLabel->Wrap(-1);
    seriesSizer->Add(seriesLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    seriesChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    setSeriesChoice();
    seriesChoice->Bind(wxEVT_CHOICE, &ReleasePickerPanel::onSelectSeries, this);
    seriesSizer->Add(seriesChoice, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(seriesSizer, 0, wxEXPAND, 5);

    auto gameSizer = new wxBoxSizer(wxHORIZONTAL);

    auto gameLabel = new wxStaticText(this, wxID_ANY, wxT("Game"), wxDefaultPosition, wxDefaultSize, 0);
    gameLabel->Wrap(-1);
    gameSizer->Add(gameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    gameChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    setGameChoice();
    gameChoice->Bind(wxEVT_CHOICE, &ReleasePickerPanel::onSelectGame, this);
    gameSizer->Add(gameChoice, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(gameSizer, 0, wxEXPAND, 5);

    auto releaseSizer = new wxBoxSizer(wxHORIZONTAL);

    auto releaseLabel = new wxStaticText(this, wxID_ANY, wxT("Release"), wxDefaultPosition, wxDefaultSize, 0);
    releaseLabel->Wrap(-1);
    releaseSizer->Add(releaseLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    releaseChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    setReleaseChoice();
    releaseSizer->Add(releaseChoice, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(releaseSizer, 0, wxEXPAND, 5);

    auto selectButton = new wxButton(this, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0);
    selectButton->Bind(wxEVT_BUTTON, &ReleasePickerPanel::onSelect, this);
    mainSizer->Add(selectButton, 0, wxALL | wxEXPAND, 5);


    this->SetSizer(mainSizer);
    this->Layout();
}

void ReleasePickerPanel::setSeriesChoice() {
    auto seriesChoices = wxArrayString();
    series = chartManager.getGameManager().getSeries();

    if(series.empty()) {
        throw std::runtime_error("No series available");
    }

    for(const auto& seriesItem : series) {
        seriesChoices.Add(seriesItem.name);
    }

    seriesChoice->Set(seriesChoices);
    seriesChoice->SetSelection(0);
}

void ReleasePickerPanel::setGameChoice() {
    auto gameChoices = wxArrayString();
    games = chartManager.getGameManager().getGamesBySeries(series[seriesChoice->GetSelection()].id);

    if(games.empty()) {
        throw std::runtime_error("No games available");
    }

    for(const auto& game : games) {
        gameChoices.Add(game.name);
    }

    gameChoice->Set(gameChoices);
    gameChoice->SetSelection(0);
}

void ReleasePickerPanel::setReleaseChoice() {
    auto releaseChoices = wxArrayString();
    releases = chartManager.getGameManager().getReleasesByGame(games[gameChoice->GetSelection()].id);

    if(releases.empty()) {
        throw std::runtime_error("No releases available");
    }

    for(const auto& releaseItem : releases) {
        releaseChoices.Add(releaseItem.code);
    }

    releaseChoice->Set(releaseChoices);
    releaseChoice->SetSelection(0);
}

void ReleasePickerPanel::onSelect(wxCommandEvent& event) {
    this->releaseInfo = ReleaseInfo{series[seriesChoice->GetSelection()], games[gameChoice->GetSelection()], releases[releaseChoice->GetSelection()]};
    this->GetParent()->Close();
}

void ReleasePickerPanel::onSelectSeries(wxCommandEvent& event) {
    setGameChoice();
    setReleaseChoice();
}

void ReleasePickerPanel::onSelectGame(wxCommandEvent& event) {
    setReleaseChoice();
}
