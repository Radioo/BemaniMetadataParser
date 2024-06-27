//
// Created by Radio on 26/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXPARSERPANEL_HPP
#define BEMANIMETADATAPARSER_SDVXPARSERPANEL_HPP

#include "ChartManager.hpp"
#include "Model/ReleaseInfo.hpp"

#include <optional>
#include <unordered_map>
#include <wx/wx.h>
#include <wx/filepicker.h>
#include <wx/treelist.h>

class SDVXParserPanel : public wxPanel {
public:
    SDVXParserPanel(wxWindow* parent, ChartManager& chartManager, std::optional<ReleaseInfo>& releaseInfo);
private:
    ChartManager& chartManager;
    std::optional<ReleaseInfo>& releaseInfo;
    wxTreeListCtrl* parsedDataTreeList;
    std::vector<SDVXParsedSong> parsedSongs;
    std::unordered_map<wxTreeListModelNode*, SDVXParsedSong*> parsedSongsMap;
    std::unordered_map<wxTreeListModelNode*, SDVXParsedChart*> parsedChartsMap;

    void loadTreeData();
    void onFileChanged(wxFileDirPickerEvent& event);
    void onTreeItemRightClick(wxTreeListEvent& event);
    wxMenu* getSongContextMenu(SDVXParsedSong* song);
};


#endif //BEMANIMETADATAPARSER_SDVXPARSERPANEL_HPP
