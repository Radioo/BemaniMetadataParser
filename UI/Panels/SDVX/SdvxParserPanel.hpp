//
// Created by Radio on 19/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXPARSERPANEL_HPP
#define BEMANIMETADATAPARSER_SDVXPARSERPANEL_HPP

#include <wx/wx.h>
#include "../BasePanel.hpp"

class SDVXParserPanel : public BasePanel {
public:
    explicit SDVXParserPanel(wxWindow *parent, Parser& parser);
    void afterCommit() override;
    void onPanelOpen() override;
};


#endif //BEMANIMETADATAPARSER_SDVXPARSERPANEL_HPP
