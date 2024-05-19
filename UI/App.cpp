//
// Created by Radio on 07/05/2024.
//

#include "App.hpp"
#include "Frames/BaseFrame.hpp"

#include <iostream>

bool App::OnInit() {
    auto* frame = new BaseFrame();
    frame->Show();

    return true;
}