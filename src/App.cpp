//
// Created by Radio on 20/06/2024.
//

#include "App.hpp"

bool App::OnInit() {
    try {
        throw std::runtime_error("An error occurred");
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