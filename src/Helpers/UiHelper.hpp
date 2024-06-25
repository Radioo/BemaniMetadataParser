//
// Created by Radio on 21/06/2024.
//

#ifndef BEMANIMETADATAPARSER_UIHELPER_HPP
#define BEMANIMETADATAPARSER_UIHELPER_HPP

#include <wx/wx.h>
#include <wx/grid.h>

class UIHelper {
public:
    static void setCommonGridAttributes(wxGrid* grid);
    static wxString getRowIdValue(wxGrid* grid, wxGridEvent& event);
    static wxMenu* getGridMenu();
};


#endif //BEMANIMETADATAPARSER_UIHELPER_HPP
