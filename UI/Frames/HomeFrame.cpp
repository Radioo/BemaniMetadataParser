//
// Created by Radio on 10/05/2024.
//

#include "HomeFrame.hpp"
#include "Parser.hpp"

HomeFrame::HomeFrame() : wxFrame(nullptr, wxID_ANY, "BEMANI Metadata Parser") {
    Parser parser;
    std::cout << "HomeFrame created" << std::endl;
}
