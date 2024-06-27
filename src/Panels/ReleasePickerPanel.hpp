//
// Created by Radio on 25/06/2024.
//

#ifndef BEMANIMETADATAPARSER_RELEASEPICKERPANEL_HPP
#define BEMANIMETADATAPARSER_RELEASEPICKERPANEL_HPP

#include "ChartManager.hpp"
#include "Model/ReleaseInfo.hpp"

#include <wx/wx.h>
#include <optional>

class ReleasePickerPanel : public wxPanel {
public:
    ReleasePickerPanel(wxWindow* parent, ChartManager& chartManager, std::optional<ReleaseInfo>& releaseInfo);
private:
    ChartManager& chartManager;
    std::optional<ReleaseInfo>& releaseInfo;
    wxChoice* seriesChoice;
    std::vector<Series> series;
    wxChoice* gameChoice;
    std::vector<Game> games;
    wxChoice* releaseChoice;
    std::vector<Release> releases;

    void setSeriesChoice();
    void setGameChoice();
    void setReleaseChoice();
    void onSelectSeries(wxCommandEvent& event);
    void onSelectGame(wxCommandEvent& event);
    void onSelect(wxCommandEvent& event);
};


#endif //BEMANIMETADATAPARSER_RELEASEPICKERPANEL_HPP
