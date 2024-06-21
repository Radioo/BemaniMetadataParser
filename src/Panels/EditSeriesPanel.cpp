//
// Created by Radio on 20/06/2024.
//

#include "EditSeriesPanel.hpp"

EditSeriesPanel::EditSeriesPanel(wxWindow* parent, Series* series, ChartManager& chartManager) : wxPanel(parent), series(series), chartManager(chartManager) {
    wxBoxSizer* mainSizer;
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* nameSizer;
    nameSizer = new wxBoxSizer(wxHORIZONTAL);

    auto* nameLabel = new wxStaticText(this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
    nameLabel->Wrap(-1);
    nameSizer->Add(nameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    nameTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    nameSizer->Add(nameTextCtrl, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(nameSizer, 0, wxEXPAND, 5);

    auto* saveButton = new wxButton(this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0);
    mainSizer->Add(saveButton, 0, wxALL | wxEXPAND, 5);
    Bind(wxEVT_BUTTON, &EditSeriesPanel::onSave, this, saveButton->GetId());

    this->SetSizer(mainSizer);
    this->Layout();
}

void EditSeriesPanel::onSave(wxCommandEvent& event) {
    auto value = nameTextCtrl->GetValue();
    this->chartManager.getGameManager().addSeries(value.ToStdString());
    this->GetParent()->Close();
}
