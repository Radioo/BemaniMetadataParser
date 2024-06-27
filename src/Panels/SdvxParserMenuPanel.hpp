//
// Created by Radio on 26/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXPARSERMENUPANEL_HPP
#define BEMANIMETADATAPARSER_SDVXPARSERMENUPANEL_HPP

#include "ChartManager.hpp"
#include "Model/ReleaseInfo.hpp"

#include <wx/wx.h>
#include <optional>

class SDVXParserMenuPanel : public wxPanel {
public:
    SDVXParserMenuPanel(wxWindow* parent, ChartManager& chartManager);
private:
    ChartManager& chartManager;
    wxStaticText* releaseInfoText;
    std::optional<ReleaseInfo> releaseInfo = std::nullopt;

    void onSelectRelease(wxCommandEvent& event);
    void updateReleaseInfoText();
};


#endif //BEMANIMETADATAPARSER_SDVXPARSERMENUPANEL_HPP
