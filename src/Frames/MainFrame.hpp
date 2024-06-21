//
// Created by Radio on 20/06/2024.
//

#ifndef BEMANIMETADATAPARSER_MAINFRAME_HPP
#define BEMANIMETADATAPARSER_MAINFRAME_HPP

#include <wx/wx.h>

#include "ChartManager.hpp"

class MainFrame : public wxFrame {
public:
    MainFrame(ChartManager& chartManager);
private:
    ChartManager& chartManager;
    wxPanel* currentPanel = nullptr;
    wxBoxSizer* mainSizer = nullptr;

    void setupMenuBar();
    void onExit(wxCommandEvent& event);
    void onCommit(wxCommandEvent& event);
    void switchPanel(wxPanel* panel);
};


#endif //BEMANIMETADATAPARSER_MAINFRAME_HPP
