//
// Created by Radio on 25/06/2024.
//

#ifndef BEMANIMETADATAPARSER_EDITRELEASEPANEL_HPP
#define BEMANIMETADATAPARSER_EDITRELEASEPANEL_HPP

#include "ChartManager.hpp"

#include <wx/wx.h>

class EditReleasePanel : public wxPanel {
public:
    EditReleasePanel(wxWindow* parent, Release* release, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    Release* release;
    std::vector<Game> games;
    wxChoice* gameChoice;
    wxTextCtrl* codeTextCtrl;

    void onSave(wxCommandEvent& event);
};


#endif //BEMANIMETADATAPARSER_EDITRELEASEPANEL_HPP
