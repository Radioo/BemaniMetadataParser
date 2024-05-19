//
// Created by Radio on 19/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SERIESPANEL_HPP
#define BEMANIMETADATAPARSER_SERIESPANEL_HPP

#include <wx/wx.h>
#include "Parser.hpp"
#include "../BasePanel.hpp"

class SeriesPanel : public BasePanel {
public:
    explicit SeriesPanel(wxWindow* parent, Parser& parser);

private:
    wxTextCtrl* newSeriesNameInput;
    wxButton* addNewSeriesButton;

    void onAddNewSeries(wxCommandEvent& event);
};


#endif //BEMANIMETADATAPARSER_SERIESPANEL_HPP
