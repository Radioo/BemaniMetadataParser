//
// Created by Radio on 20/06/2024.
//

#ifndef BEMANIMETADATAPARSER_EDITSERIESPANEL_HPP
#define BEMANIMETADATAPARSER_EDITSERIESPANEL_HPP

#include "model/Series.hpp"
#include "ChartManager.hpp"

#include <wx/wx.h>

class EditSeriesPanel : public wxPanel {
public:
    EditSeriesPanel(wxWindow* parent, Series* series, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    Series* series;
    wxTextCtrl* nameTextCtrl;

    void onSave(wxCommandEvent& event);
};


#endif //BEMANIMETADATAPARSER_EDITSERIESPANEL_HPP
