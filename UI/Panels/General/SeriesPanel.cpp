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

    SetSizer(mainSizer);
}

void SeriesPanel::onAddNewSeries(wxCommandEvent& event) {
    addNewSeriesButton->Disable();

    parser.seriesService.addSeries(newSeriesNameInput->GetValue().ToStdString());

    addNewSeriesButton->Enable();
}