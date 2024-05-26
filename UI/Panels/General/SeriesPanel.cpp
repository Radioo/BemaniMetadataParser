//
// Created by Radio on 19/05/2024.
//

#include "SeriesPanel.hpp"

#include <wx/statline.h>

SeriesPanel::SeriesPanel(wxWindow *parent, Parser &parser) : BasePanel(parent, parser) {
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);

    auto* newSeriesSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* newSeriesText = new wxStaticText(this, wxID_ANY, wxT("New Series"), wxDefaultPosition, wxDefaultSize, 0);
    newSeriesText->Wrap(-1);
    newSeriesSizer->Add(newSeriesText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    newSeriesNameInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    newSeriesNameInput->Bind(wxEVT_TEXT_ENTER, &SeriesPanel::onAddNewSeries, this);
    newSeriesSizer->Add(newSeriesNameInput, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    addNewSeriesButton = new wxButton(this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    addNewSeriesButton->Bind(wxEVT_BUTTON, &SeriesPanel::onAddNewSeries, this);
    newSeriesSizer->Add(addNewSeriesButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    mainSizer->Add(newSeriesSizer, 0, wxEXPAND, 5);

    auto* separator = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    mainSizer->Add(separator, 0, wxEXPAND | wxALL, 5);

    seriesGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    // Grid
    seriesGrid->CreateGrid(0, 0);
    seriesGrid->EnableEditing(false);
    seriesGrid->EnableGridLines(true);
    seriesGrid->EnableDragGridSize(false);
    seriesGrid->SetMargins(0, 0);

    // Columns
    seriesGrid->AutoSizeColumns();
    seriesGrid->EnableDragColMove(false);
    seriesGrid->EnableDragColSize(true);
    seriesGrid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

    // Rows
    seriesGrid->AutoSizeRows();
    seriesGrid->EnableDragRowSize(true);
    seriesGrid->SetRowLabelSize(wxGRID_AUTOSIZE);
    seriesGrid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

    // Cell Defaults
    seriesGrid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
    mainSizer->Add(seriesGrid, 0, wxALL|wxEXPAND, 5);

    // Set columns
    auto columns = parser.seriesService.getColumns();
    auto columnCount = static_cast<int>(columns.size());
    seriesGrid->AppendCols(columnCount);
    for(int i = 0; i < columnCount; i++) {
        seriesGrid->SetColLabelValue(i, columns[i]);
    }

    SetSizer(mainSizer);

    updateGridData();
}

void SeriesPanel::onAddNewSeries(wxCommandEvent& event) {
    try {
        addNewSeriesButton->Disable();

        parser.seriesService.addSeries(newSeriesNameInput->GetValue().ToStdString());
        newSeriesNameInput->Clear();

        addNewSeriesButton->Enable();
    }
    catch(const std::exception& e) {
        wxMessageBox(e.what(), wxT("Error"), wxICON_ERROR);
    }
}

void SeriesPanel::updateGridData() {
    auto columns = parser.seriesService.getColumns();
    auto columnCount = static_cast<int>(columns.size());
    auto data = parser.seriesService.getAllData();
    auto rowCount = static_cast<int>(data.size());

    auto currentRows = seriesGrid->GetNumberRows();
    if(currentRows > 0) {
        seriesGrid->DeleteRows(0, currentRows);
    }
    seriesGrid->AppendRows(rowCount);

    for(int i = 0; i < rowCount; i++) {
        for(int j = 0; j < columnCount; j++) {
            seriesGrid->SetCellValue(i, j, data[i][j]);
        }
    }

    seriesGrid->AutoSizeColumns();
    Layout();
}

void SeriesPanel::afterCommit() {
    updateGridData();
}

void SeriesPanel::onPanelOpen() {

}
