//
// Created by Radio on 19/05/2024.
//

#ifndef BEMANIMETADATAPARSER_HOMEPANEL_HPP
#define BEMANIMETADATAPARSER_HOMEPANEL_HPP

#include <wx/wx.h>
#include "BasePanel.hpp"

class HomePanel : public BasePanel {
public:
    explicit HomePanel(wxWindow* parent, Parser& parser);
};


#endif //BEMANIMETADATAPARSER_HOMEPANEL_HPP
