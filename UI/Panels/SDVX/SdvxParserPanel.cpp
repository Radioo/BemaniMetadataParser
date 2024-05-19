//
// Created by Radio on 19/05/2024.
//

#include "SdvxParserPanel.hpp"

SDVXParserPanel::SDVXParserPanel(wxWindow *parent, Parser &parser) : BasePanel(parent, parser) {
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "SDVX Parser");
}
