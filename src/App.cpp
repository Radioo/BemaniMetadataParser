//
// Created by Radio on 20/06/2024.
//

#include "App.hpp"
#include "ChartManager.hpp"
#include "Frames/MainFrame.hpp"

bool App::OnInit() {
    try {
        auto* mainFrame = new MainFrame();
        mainFrame->Show();
    }
    catch(std::exception& e) {
        wxMessageBox(e.what(), "Error", wxICON_ERROR);
        return false;
    }
    catch(...) {
        wxMessageBox("An unknown error occurred", "Error", wxICON_ERROR);
        return false;
    }

    return true;
}