//
// Created by Radio on 26/05/2024.
//

#include <wx/grid.h>
#include <wx/statline.h>
#include "ReleasePanel.hpp"

ReleasePanel::ReleasePanel(wxWindow *parent, Parser &parser) : BasePanel(parent, parser) {
    auto mainSizer = new wxBoxSizer( wxVERTICAL );

    newReleaseErrorText = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    newReleaseErrorText->Wrap( -1 );
    newReleaseErrorText->Hide();
    mainSizer->Add( newReleaseErrorText, 0, wxALL, 5 );

    auto newReleaseSizer = new wxBoxSizer( wxHORIZONTAL );

    auto newReleaseText = new wxStaticText( this, wxID_ANY, wxT("New Release"), wxDefaultPosition, wxDefaultSize, 0 );
    newReleaseText->Wrap( -1 );
    newReleaseSizer->Add( newReleaseText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    wxArrayString newReleaseGameSelectChoices;
    newReleaseGameSelect = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, newReleaseGameSelectChoices, 0 );
    newReleaseGameSelect->SetSelection( 0 );
    newReleaseSizer->Add( newReleaseGameSelect, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    newReleaseCode = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    newReleaseSizer->Add( newReleaseCode, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    addNewReleaseButton = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
    addNewReleaseButton->Disable();
    addNewReleaseButton->Bind( wxEVT_BUTTON, &ReleasePanel::onAddRelease, this );
    newReleaseSizer->Add( addNewReleaseButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


    mainSizer->Add( newReleaseSizer, 0, wxEXPAND, 5 );

    auto separator = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    mainSizer->Add( separator, 0, wxEXPAND | wxALL, 5 );

    releaseGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    // Grid
    releaseGrid->CreateGrid( 0, 0 );
    releaseGrid->EnableEditing( true );
    releaseGrid->EnableGridLines( true );
    releaseGrid->EnableDragGridSize( false );
    releaseGrid->SetMargins( 0, 0 );

    // Columns
    releaseGrid->EnableDragColMove( false );
    releaseGrid->EnableDragColSize( true );
    releaseGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

    // Rows
    releaseGrid->EnableDragRowSize( true );
    releaseGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

    // Cell Defaults
    releaseGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
    mainSizer->Add( releaseGrid, 1, wxALL|wxEXPAND, 5 );

    // Set Columns
    auto columns = parser.releaseService.getColumns();
    auto columnCount = static_cast<int>(columns.size());
    releaseGrid->AppendCols(columnCount);
    for(int i = 0; i < columnCount; i++) {
        releaseGrid->SetColLabelValue(i, columns[i]);
    }

    this->SetSizer( mainSizer );
    this->Layout();
}

void ReleasePanel::afterCommit() {
    refreshData();
}

void ReleasePanel::onPanelOpen() {
    refreshData();
}

void ReleasePanel::onAddRelease(wxCommandEvent &event) {
    try {
        addNewReleaseButton->Disable();

        auto selectedGameIndex = newReleaseGameSelect->GetSelection();
        auto [gameId, gameName] = games[selectedGameIndex];
        auto code = newReleaseCode->GetValue().ToStdString();

        ReleaseService::addRelease(gameId, std::move(code));
        newReleaseCode->Clear();

        addNewReleaseButton->Enable();
    }
    catch(std::exception& e) {
        wxMessageBox(e.what(), wxT("Error"), wxICON_ERROR);
    }
}

void ReleasePanel::refreshData() {
    try {
        games = GameService::getGames();
        if(games.empty()) {
            newReleaseErrorText->SetLabelText("No games found. Please add a game first.");
            newReleaseErrorText->Show();
            addNewReleaseButton->Disable();
        }
        else {
            newReleaseErrorText->Hide();
            addNewReleaseButton->Enable();
        }

        newReleaseGameSelect->Clear();
        for(const auto& [id, name] : games) {
            newReleaseGameSelect->Append(name);
        }
        newReleaseGameSelect->SetSelection(0);

        auto columns = parser.releaseService.getColumns();
        auto data = parser.releaseService.getAllData();
        auto columnCount = static_cast<int>(columns.size());
        auto rowCount = static_cast<int>(data.size());

        auto currentRows = releaseGrid->GetNumberRows();
        if(currentRows > 0) {
            releaseGrid->DeleteRows(0, currentRows);
        }
        releaseGrid->AppendRows(rowCount);

        for(int i = 0; i < rowCount; i++) {
            for(int j = 0; j < columnCount; j++) {
                releaseGrid->SetCellValue(i, j, data[i][j]);
            }
        }

        releaseGrid->AutoSizeColumns();
        this->Layout();
    }
    catch(std::exception& e) {
        wxMessageBox(e.what(), wxT("Error"), wxICON_ERROR);
    }
}
