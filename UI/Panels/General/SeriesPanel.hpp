//
// Created by Radio on 19/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SERIESPANEL_HPP
#define BEMANIMETADATAPARSER_SERIESPANEL_HPP

#include <wx/wx.h>
#include <wx/grid.h>
#include "Parser.hpp"
#include "../BasePanel.hpp"

class SeriesPanel : public BasePanel {
public:
    explicit SeriesPanel(wxWindow* parent, Parser& parser);
    void afterCommit() override;

private:
    wxTextCtrl* newSeriesNameInput;
    wxButton* addNewSeriesButton;
    wxGrid* seriesGrid;

    void onAddNewSeries(wxCommandEvent& event);
    void updateGridData();
};


#endif //BEMANIMETADATAPARSER_SERIESPANEL_HPP
