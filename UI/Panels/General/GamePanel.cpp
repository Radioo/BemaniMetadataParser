//
// Created by Radio on 26/05/2024.
//

#include <wx/statline.h>
#include "GamePanel.hpp"

GamePanel::GamePanel(wxWindow *parent, Parser &parser) : BasePanel(parent, parser) {
    auto mainSizer = new wxBoxSizer( wxVERTICAL );

    newGameErrorText = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    newGameErrorText->Wrap( -1 );
    newGameErrorText->Hide();
    mainSizer->Add( newGameErrorText, 0, wxALL|wxEXPAND, 5 );

    auto newGameSizer = new wxBoxSizer( wxHORIZONTAL );

    auto newGameText = new wxStaticText( this, wxID_ANY, wxT("New Game"), wxDefaultPosition, wxDefaultSize, 0 );
    newGameText->Wrap( -1 );
    newGameSizer->Add( newGameText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    wxArrayString newGameSeriesSelectChoices;
    newGameSeriesSelect = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, newGameSeriesSelectChoices, 0 );
    newGameSeriesSelect->SetSelection( 0 );
    newGameSizer->Add( newGameSeriesSelect, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    newGameName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    newGameSizer->Add( newGameName, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    newGameVersion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    newGameSizer->Add( newGameVersion, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    addNewGameButton = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
    addNewGameButton->Disable();
    addNewGameButton->Bind( wxEVT_BUTTON, &GamePanel::onAddNewGame, this );
    newGameSizer->Add( addNewGameButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


    mainSizer->Add( newGameSizer, 0, wxEXPAND, 5 );

    auto separator = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    mainSizer->Add( separator, 0, wxEXPAND | wxALL, 5 );

    gameGrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

    // Grid
    gameGrid->CreateGrid( 0, 0 );
    gameGrid->EnableEditing( false );
    gameGrid->EnableGridLines( true );
    gameGrid->EnableDragGridSize( false );
    gameGrid->SetMargins( 0, 0 );

    // Columns
    gameGrid->AutoSizeColumns();
    gameGrid->EnableDragColMove( false );
    gameGrid->EnableDragColSize( true );
    gameGrid->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

    // Rows
    gameGrid->AutoSizeRows();
    gameGrid->EnableDragRowSize( true );
    gameGrid->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

    // Cell Defaults
    gameGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
    mainSizer->Add( gameGrid, 1, wxALL|wxEXPAND, 5 );

    // Set columns
    auto columns = parser.gameService.getColumns();
    auto columnCount = static_cast<int>(columns.size());
    gameGrid->AppendCols(columnCount);
    for(int i = 0; i < columnCount; i++) {
        gameGrid->SetColLabelValue(i, columns[i]);
    }

    this->SetSizer( mainSizer );
    this->Layout();
}

void GamePanel::afterCommit() {
    refreshData();
}

void GamePanel::onPanelOpen() {
    refreshData();
}

void GamePanel::refreshData() {
    try {
        series = SeriesService::getSeries();
        if(series.empty()) {
            newGameErrorText->SetLabelText("No series found. Please add a series first.");
            newGameErrorText->Show();
            addNewGameButton->Disable();
        }
        else {
            newGameErrorText->Hide();
            addNewGameButton->Enable();
        }

        newGameSeriesSelect->Clear();
        for(const auto& [id, name] : series) {
            newGameSeriesSelect->Append(name);
        }
        newGameSeriesSelect->SetSelection(0);

        auto columns = parser.gameService.getColumns();
        auto data = parser.gameService.getAllData();
        auto columnCount = static_cast<int>(columns.size());
        auto rowCount = static_cast<int>(data.size());

        auto currentRows = gameGrid->GetNumberRows();
        if(currentRows > 0) {
            gameGrid->DeleteRows(0, currentRows);
        }
        gameGrid->AppendRows(rowCount);

        for(int i = 0; i < rowCount; i++) {
            for(int j = 0; j < columnCount; j++) {
                gameGrid->SetCellValue(i, j, data[i][j]);
            }
        }

        gameGrid->AutoSizeColumns();
        this->Layout();
    }
    catch(const std::exception& e) {
        wxMessageBox(e.what(), wxT("Error"), wxICON_ERROR);
    }
}

void GamePanel::onAddNewGame(wxCommandEvent &event) {
    try {
        addNewGameButton->Disable();

        auto selectedSeriesIndex = newGameSeriesSelect->GetSelection();
        GameService::addGame(
                std::get<0>(series[selectedSeriesIndex]),
                newGameName->GetValue().ToStdString(),
                std::stoi(newGameVersion->GetValue().ToStdString())
        );
        newGameName->Clear();
        newGameVersion->Clear();

        addNewGameButton->Enable();
    }
    catch(const std::exception& e) {
        wxMessageBox(e.what(), wxT("Error"), wxICON_ERROR);
    }
}
