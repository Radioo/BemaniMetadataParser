//
// Created by Radio on 26/06/2024.
//

#include "SdvxParserMenuPanel.hpp"
#include "ReleasePickerPanel.hpp"
#include "SdvxParserPanel.hpp"

SDVXParserMenuPanel::SDVXParserMenuPanel(wxWindow* parent, ChartManager& chartManager) : wxPanel(parent), chartManager(chartManager) {
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto releaseSizer = new wxBoxSizer(wxHORIZONTAL);

    auto releaseLabel = new wxStaticText(this, wxID_ANY, wxT("Release"), wxDefaultPosition, wxDefaultSize, 0);
    releaseLabel->Wrap(-1);
    releaseSizer->Add(releaseLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    releaseInfoText = new wxStaticText(this, wxID_ANY, wxT("Please select a release"), wxDefaultPosition, wxDefaultSize,
                                       wxALIGN_CENTER_HORIZONTAL);
    releaseInfoText->Wrap(-1);
    releaseSizer->Add(releaseInfoText, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto releaseButton = new wxButton(this, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0);
    releaseButton->Bind(wxEVT_BUTTON, &SDVXParserMenuPanel::onSelectRelease, this);
    releaseSizer->Add(releaseButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);


    mainSizer->Add(releaseSizer, 0, wxEXPAND, 5);

    auto parserPanel = new SDVXParserPanel(this, chartManager, releaseInfo);
    mainSizer->Add(parserPanel, 1, wxEXPAND, 5);


    this->SetSizer(mainSizer);
    this->Layout();
}

void SDVXParserMenuPanel::onSelectRelease(wxCommandEvent& event) {
    auto* dialog = new wxDialog(this, wxID_ANY, wxT("Select Release"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    auto* panel = new ReleasePickerPanel(dialog, this->chartManager, releaseInfo);
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND, 5);
    dialog->SetSizer(sizer);
    dialog->Fit();
    dialog->ShowModal();
    updateReleaseInfoText();
}

void SDVXParserMenuPanel::updateReleaseInfoText() {
    if(releaseInfo == std::nullopt) {
        releaseInfoText->SetLabelText(wxEmptyString);
        return;
    }

    releaseInfoText->SetLabelText(releaseInfo->series.name + " - " + releaseInfo->game.name + " - " + releaseInfo->release.code);
    this->Layout();
}
