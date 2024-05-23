//
// Created by Radio on 07/05/2024.
//

#include "App.hpp"
#include "Frames/BaseFrame.hpp"

#include <iostream>
#include <filesystem>

bool App::OnInit() {
    if(!std::filesystem::exists("data")) {
        std::filesystem::create_directory("data");
    }

    try {
        Parser parser;
        Parser::initialize();
        auto* frame = new BaseFrame(parser);
        frame->Show();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}