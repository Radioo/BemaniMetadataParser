//
// Created by Radio on 18/05/2024.
//

#include "BaseFrame.hpp"
#include "../Panels/HomePanel.hpp"
#include "../Enums/MenuItem.hpp"
#include "../Panels/SDVX/SdvxParserPanel.hpp"
#include "../Panels/General/SeriesPanel.hpp"

#include <type_traits>

typedef std::underlying_type<MenuItem>::type MenuItemType;

BaseFrame::BaseFrame(Parser parser) : wxFrame(nullptr, wxID_ANY, wxT("BEMANI Metadata Parser")), parser(parser) {
    setupMenuBar();

    simpleBook = new wxSimplebook(this, wxID_ANY);

    setupHomePanel();
    setupSeriesPanel();
    setupSDVXParserPanel();

    changePage(Page::Home);

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(simpleBook, 1, wxEXPAND);
}

void BaseFrame::setupMenuBar() {
    // File
    auto* fileOptions = new wxMenu;

    fileOptions->Append(static_cast<MenuItemType>(MenuItem::Home), wxT("Home"));
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::Home);
    }, static_cast<MenuItemType>(MenuItem::Home));

    fileOptions->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &BaseFrame::onExit, this, wxID_EXIT);

    // DB
    auto dbOptions = new wxMenu;

    dbOptions->Append(static_cast<MenuItemType>(MenuItem::CommitDb), wxT("Commit"));
    Bind(wxEVT_MENU, &BaseFrame::onCommitDb, this, static_cast<MenuItemType>(MenuItem::CommitDb));

    // General
    auto* generalOptions = new wxMenu;

    generalOptions->Append(static_cast<MenuItemType>(MenuItem::Series), wxT("Series"));
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::Series);
    }, static_cast<MenuItemType>(MenuItem::Series));

    generalOptions->Append(static_cast<MenuItemType>(MenuItem::Game), wxT("Game"));
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::Game);
    }, static_cast<MenuItemType>(MenuItem::Game));

    generalOptions->Append(static_cast<MenuItemType>(MenuItem::Release), wxT("Release"));
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::Release);
    }, static_cast<MenuItemType>(MenuItem::Release));

    // SDVX
    auto* sdvxOptions = new wxMenu;

    sdvxOptions->Append(static_cast<MenuItemType>(MenuItem::SDVXParser), wxT("Parser"));
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::SDVXParser);
    }, static_cast<MenuItemType>(MenuItem::SDVXParser));

    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileOptions, wxT("File"));
    menuBar->Append(dbOptions, wxT("DB"));
    menuBar->Append(generalOptions, wxT("General"));
    menuBar->Append(sdvxOptions, wxT("SDVX"));

    SetMenuBar(menuBar);

    CreateStatusBar();
    Parser::setOnUncommitedChangesChangeCallback([this] {
        std::string statusText = "Uncommited changes: " + std::to_string(Parser::getUncommitedChanges());
        SetStatusText(statusText);
    });
}


void BaseFrame::onExit([[maybe_unused]] wxCommandEvent& event) {
    Close();
}

void BaseFrame::addPage(Page page, wxWindow *panel, const wxString &title) {
    pageMap[page] = simpleBook->GetPageCount();
    simpleBook->AddPage(panel, title);
}

void BaseFrame::changePage(Page page) {
    simpleBook->ChangeSelection(pageMap[page]);
    auto panel = (BasePanel*) simpleBook->GetCurrentPage();
    Parser::setAfterCommitCallback([panel] {
        panel->afterCommit();
    });
}

void BaseFrame::setupHomePanel() {
    auto* homePanel = new HomePanel(simpleBook, parser);
    addPage(Page::Home, homePanel, wxT("Home"));
}

void BaseFrame::setupSDVXParserPanel() {
    auto* sdvxParserPanel = new SDVXParserPanel(simpleBook, parser);
    addPage(Page::SDVXParser, sdvxParserPanel, wxT("SDVX Parser"));
}

void BaseFrame::setupSeriesPanel() {
    auto* seriesPanel = new SeriesPanel(simpleBook, parser);
    addPage(Page::Series, seriesPanel, wxT("Series"));
}

void BaseFrame::onCommitDb(wxCommandEvent &event) {
    try {
        Parser::commit();
    }
    catch(const std::exception& e) {
        wxMessageBox(e.what(), wxT("Error"), wxICON_ERROR);
    }
}
