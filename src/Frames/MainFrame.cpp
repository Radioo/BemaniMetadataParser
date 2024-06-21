//
// Created by Radio on 20/06/2024.
//

#include "MainFrame.hpp"
#include "../Panels/SeriesPanel.hpp"
#include "../Enums/MenuOption.hpp"

MainFrame::MainFrame(ChartManager& chartManager) : wxFrame(nullptr, wxID_ANY, wxT("Bemani Metadata Parser"), wxDefaultPosition, {1280, 780}), chartManager(chartManager) {
    this->setupMenuBar();
}

void MainFrame::setupMenuBar() {
    auto* fileOptions = new wxMenu;

    fileOptions->Append(static_cast<int>(MenuOption::COMMIT), wxT("Commit"));
    Bind(wxEVT_MENU, &MainFrame::onCommit, this, static_cast<int>(MenuOption::COMMIT));

    fileOptions->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::onExit, this, wxID_EXIT);

    auto* generalOptions = new wxMenu;
    generalOptions->Append(static_cast<int>(MenuOption::SERIES), wxT("Series"));
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {this->switchPanel(new SeriesPanel(this, this->chartManager));}, static_cast<int>(MenuOption::SERIES));

    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileOptions, wxT("File"));
    menuBar->Append(generalOptions, wxT("General"));

    SetMenuBar(menuBar);
}

void MainFrame::onExit(wxCommandEvent& event) {
    Close();
}

void MainFrame::switchPanel(wxPanel* panel) {
    if(this->currentPanel != nullptr) {
        this->currentPanel->Close();
    }

    this->currentPanel = panel;
    Layout();
}

void MainFrame::onCommit(wxCommandEvent& event) {
    this->chartManager.commit();
}
