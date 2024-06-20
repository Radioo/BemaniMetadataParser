//
// Created by Radio on 20/06/2024.
//

#include "SeriesPanel.hpp"

SeriesPanel::SeriesPanel(wxFrame* parent) : wxPanel(parent) {
    wxBoxSizer* mainSizer;
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* headerSizer;
    headerSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* addSeriesButton = new wxButton(this, wxID_ANY, wxT("Add Series"), wxDefaultPosition, wxDefaultSize, 0);
    headerSizer->Add(addSeriesButton, 0, wxALL, 5);

    mainSizer->Add(headerSizer, 1, wxEXPAND, 5);

    this->SetSizer(mainSizer);
    this->Layout();
}
