//
// Created by Radio on 20/06/2024.
//

#include "App.hpp"
#include "ChartManager.hpp"
#include "Frames/MainFrame.hpp"

bool App::OnInit() {
    ChartManager chartManager({});
    auto* mainFrame = new MainFrame(chartManager);
    mainFrame->Show();

    return true;
}

bool App::OnExceptionInMainLoop() {
    try {
        throw;
    }
    catch(std::exception& e) {
        wxMessageBox(e.what(), "Error", wxICON_ERROR);
    }
    catch(...) {
        wxMessageBox("An unknown error occurred", "Error", wxICON_ERROR);
    }

    return true;
}
