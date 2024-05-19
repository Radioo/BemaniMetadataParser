//
// Created by Radio on 18/05/2024.
//

#include "BaseFrame.hpp"
#include "../Panels/HomePanel.hpp"
#include "../Enums/MenuItem.hpp"
#include "../Panels/SDVX/SdvxParserPanel.hpp"

#include <type_traits>

typedef std::underlying_type<MenuItem>::type MenuItemType;

BaseFrame::BaseFrame() : wxFrame(nullptr, wxID_ANY, "BEMANI Metadata Parser") {
    setupMenuBar();

    simpleBook = new wxSimplebook(this, wxID_ANY);

    setupHomePanel();
    setupSDVXParserPanel();

    changePage(Page::Home);

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(simpleBook, 1, wxEXPAND);
}

void BaseFrame::setupMenuBar() {
    // File
    auto* fileOptions = new wxMenu;

    fileOptions->Append(static_cast<MenuItemType>(MenuItem::Home), "Home");
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::Home);
    }, static_cast<MenuItemType>(MenuItem::Home));

    fileOptions->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &BaseFrame::onExit, this, wxID_EXIT);


    // SDVX
    auto* sdvxOptions = new wxMenu;

    sdvxOptions->Append(static_cast<MenuItemType>(MenuItem::SDVXParser), "Parser");
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) {
        changePage(Page::SDVXParser);
    }, static_cast<MenuItemType>(MenuItem::SDVXParser));

    auto* menuBar = new wxMenuBar;
    menuBar->Append(fileOptions, "File");
    menuBar->Append(sdvxOptions, "SDVX");

    SetMenuBar(menuBar);
}


void BaseFrame::onExit([[maybe_unused]] wxCommandEvent& event) {
    Close();
}

void BaseFrame::addPage(Page page, wxWindow *panel, const wxString &title) {
    if(pageMap.count(page) > 0) {
        throw std::runtime_error("Page already registered");
    }

    pageMap[page] = simpleBook->GetPageCount();
    simpleBook->AddPage(panel, title);
}

void BaseFrame::changePage(Page page) {
    if(pageMap.count(page) == 0) {
        throw std::runtime_error("Page not registered");
    }

    simpleBook->ChangeSelection(pageMap[page]);
}

void BaseFrame::setupHomePanel() {
    auto* homePanel = new HomePanel(simpleBook);
    addPage(Page::Home, homePanel, "Home");
}

void BaseFrame::setupSDVXParserPanel() {
    auto* sdvxParserPanel = new SDVXParserPanel(simpleBook);
    addPage(Page::SDVXParser, sdvxParserPanel, "SDVX Parser");
}
