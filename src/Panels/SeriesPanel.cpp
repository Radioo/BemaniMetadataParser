//
// Created by Radio on 20/06/2024.
//

#include "SeriesPanel.hpp"
#include "EditSeriesPanel.hpp"
#include "../Helpers/UiHelper.hpp"

SeriesPanel::SeriesPanel(wxWindow* parent, ChartManager& chartManager) : wxPanel(parent), chartManager(chartManager) {
    wxBoxSizer* mainSizer;
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* headerSizer;
    headerSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* addSeriesButton = new wxButton(this, wxID_ANY, wxT("Add Series"), wxDefaultPosition, wxDefaultSize, 0);
    headerSizer->Add(addSeriesButton, 0, wxALL, 5);
    Bind(wxEVT_BUTTON, &SeriesPanel::openSeriesEditor, this, addSeriesButton->GetId());

    mainSizer->Add(headerSizer, 0, wxEXPAND, 5);

    seriesGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    UIHelper::setCommonGridAttributes(seriesGrid);

    mainSizer->Add(seriesGrid, 1, wxALL | wxEXPAND, 5);

    this->SetSizer(mainSizer);
    this->Layout();

    loadData();
}

void SeriesPanel::loadData() {
    auto series = this->chartManager.getGameManager().getSeries();
    auto count = static_cast<std::int32_t>(series.size());
    auto table = new wxGridStringTable(count, 2);

    table->SetColLabelValue(0, wxT("id"));
    table->SetColLabelValue(1, wxT("name"));

    for(std::int32_t i = 0; i < count; i++) {
        table->SetValue(i, 0, std::to_string(series[i].id));
        table->SetValue(i, 1, series[i].name);
    }

    seriesGrid->SetTable(table, true);
    seriesGrid->AutoSizeColumns();
}

void SeriesPanel::openSeriesEditor(wxCommandEvent& event) {
    auto* dialog = new wxDialog(this, wxID_ANY, wxT("Add Series"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    auto* panel = new EditSeriesPanel(dialog, nullptr, this->chartManager);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND, 5);
    dialog->SetSizer(sizer);
    dialog->Fit();
    dialog->ShowModal();
    loadData();
}
