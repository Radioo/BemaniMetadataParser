//
// Created by Radio on 25/06/2024.
//

#include "ReleasePanel.hpp"
#include "EditReleasePanel.hpp"
#include "../Helpers/UiHelper.hpp"

ReleasePanel::ReleasePanel(wxWindow* parent, ChartManager& chartManager) : wxPanel(parent), chartManager(chartManager) {
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto headerSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* addReleaseButton = new wxButton(this, wxID_ANY, wxT("Add Release"), wxDefaultPosition, wxDefaultSize, 0);
    headerSizer->Add(addReleaseButton, 0, wxALL, 5);
    Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        this->openReleaseEditor(event, nullptr);
    }, addReleaseButton->GetId());

    mainSizer->Add(headerSizer, 0, wxEXPAND, 5);

    releaseGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    UIHelper::setCommonGridAttributes(releaseGrid);
    Bind(wxEVT_GRID_CELL_RIGHT_CLICK, [this](wxGridEvent& event) {
        auto releaseId = std::stoi(UIHelper::getRowIdValue(releaseGrid, event).ToStdString());

        auto* menu = UIHelper::getGridMenu();
        Bind(wxEVT_MENU, [this, &releaseId](wxCommandEvent& event) {
            auto release = this->chartManager.getGameManager().getRelease(releaseId);
            this->openReleaseEditor(event, &release);
        }, wxID_EDIT);
        Bind(wxEVT_MENU, [this, &releaseId](wxCommandEvent& event) {
            this->chartManager.getGameManager().deleteRelease(releaseId);
            this->loadData();
        }, wxID_DELETE);

        PopupMenu(menu);
    });

    mainSizer->Add(releaseGrid, 1, wxALL | wxEXPAND, 5);

    this->SetSizer(mainSizer);
    this->Layout();

    loadData();
}

void ReleasePanel::loadData() {
    auto releases = this->chartManager.getGameManager().getReleases();
    auto count = static_cast<std::int32_t>(releases.size());
    auto table = new wxGridStringTable(count, 3);

    table->SetColLabelValue(0, wxT("id"));
    table->SetColLabelValue(1, wxT("game_id"));
    table->SetColLabelValue(2, wxT("code"));

    for(std::int32_t i = 0; i < count; i++) {
        auto release = releases[i];
        table->SetValue(i, 0, std::to_string(release.id));
        table->SetValue(i, 1, std::to_string(release.gameId));
        table->SetValue(i, 2, release.code);
    }

    releaseGrid->SetTable(table, true);
    releaseGrid->AutoSizeColumns();
}

void ReleasePanel::openReleaseEditor(wxCommandEvent& event, Release* release) {
    auto* dialog = new wxDialog(this, wxID_ANY, wxT("Edit Release"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    auto* panel = new EditReleasePanel(dialog, release, this->chartManager);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND, 5);
    dialog->SetSizer(sizer);
    dialog->Fit();
    dialog->ShowModal();
    loadData();
}
