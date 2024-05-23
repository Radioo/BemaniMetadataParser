//
// Created by Radio on 19/05/2024.
//

#ifndef BEMANIMETADATAPARSER_BASEPANEL_HPP
#define BEMANIMETADATAPARSER_BASEPANEL_HPP

#include <wx/wx.h>
#include "Parser.hpp"

class BasePanel : public wxPanel {
public:
    explicit BasePanel(wxWindow* parent, Parser& parser);
    virtual void afterCommit() = 0;

protected:
    Parser& parser;
};


#endif //BEMANIMETADATAPARSER_BASEPANEL_HPP
