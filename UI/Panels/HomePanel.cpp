//
// Created by Radio on 19/05/2024.
//

#include "HomePanel.hpp"

HomePanel::HomePanel(wxWindow *parent, Parser &parser) : BasePanel(parent, parser) {
    new wxStaticText(this, wxID_ANY, "Home Panel");
}

void HomePanel::afterCommit() {}
