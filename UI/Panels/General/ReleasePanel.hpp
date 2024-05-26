//
// Created by Radio on 26/05/2024.
//

#ifndef BEMANIMETADATAPARSER_RELEASEPANEL_HPP
#define BEMANIMETADATAPARSER_RELEASEPANEL_HPP


#include "../BasePanel.hpp"

class ReleasePanel : public BasePanel {
public:
    explicit ReleasePanel(wxWindow* parent, Parser& parser);
    void afterCommit() override;
    void onPanelOpen() override;

private:
    wxButton* addNewReleaseButton;
    wxChoice* newReleaseGameSelect;
    wxStaticText* newReleaseErrorText;
    wxGrid* releaseGrid;
    wxTextCtrl* newReleaseCode;
    std::vector<std::tuple<std::uint32_t, std::string>> games;

    void onAddRelease(wxCommandEvent& event);
    void refreshData();
};


#endif //BEMANIMETADATAPARSER_RELEASEPANEL_HPP
