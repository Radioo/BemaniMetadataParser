//
// Created by Radio on 20/06/2024.
//

#ifndef BEMANIMETADATAPARSER_APP_HPP
#define BEMANIMETADATAPARSER_APP_HPP

#include <wx/wx.h>

class App : public wxApp {
public:
    bool OnInit() override;
    bool OnExceptionInMainLoop() override;
};


#endif //BEMANIMETADATAPARSER_APP_HPP
