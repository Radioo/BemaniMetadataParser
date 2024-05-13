//
// Created by Radio on 07/05/2024.
//

#include "App.hpp"
#include "Frames/HomeFrame.hpp"

#include <Parser.hpp>
#include <iostream>

bool App::OnInit() {
    auto* homeFrame = new HomeFrame();
    homeFrame->Show(true);
    return true;
}
