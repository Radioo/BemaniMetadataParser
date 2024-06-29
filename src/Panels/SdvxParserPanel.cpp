//
// Created by Radio on 26/06/2024.
//

#include "SdvxParserPanel.hpp"
#include "ReleasePickerPanel.hpp"

SDVXParserPanel::SDVXParserPanel(wxWindow* parent, ChartManager& chartManager, std::optional<ReleaseInfo>& releaseInfo) : wxPanel(parent), chartManager(chartManager), releaseInfo(releaseInfo) {
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto musicDbSizer = new wxBoxSizer(wxHORIZONTAL);

    auto musicDbLabel = new wxStaticText(this, wxID_ANY, wxT("music_db.xml"), wxDefaultPosition, wxDefaultSize, 0);
    musicDbLabel->Wrap(-1);
    musicDbSizer->Add(musicDbLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    auto musicDbPicker = new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"),
                                              wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE);
    musicDbPicker->Bind(wxEVT_FILEPICKER_CHANGED, &SDVXParserPanel::onFileChanged, this);
    musicDbSizer->Add(musicDbPicker, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    mainSizer->Add(musicDbSizer, 0, wxEXPAND, 5);

    auto actionsSizer = new wxBoxSizer(wxHORIZONTAL);
    auto hideMatchedButton = new wxButton(this, wxID_ANY, wxT("Hide matched"), wxDefaultPosition, wxDefaultSize, 0);
    actionsSizer->Add(hideMatchedButton, 0, wxALL, 5);
    hideMatchedButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        auto it = parsedSongs.begin();

        while(it != parsedSongs.end()) {
            auto chartIt = it->charts.begin();

            while(chartIt != it->charts.end()) {
                if(chartIt->chartEntryParseStatus == ParseStatus::EXISTS) {
                    chartIt = it->charts.erase(chartIt);
                }
                else {
                    chartIt++;
                }
            }

            if(it->charts.empty()) {
                it = parsedSongs.erase(it);
            }
            else {
                it++;
            }
        }

        loadTreeData();
    });

    auto addNewSongsButton = new wxButton(this, wxID_ANY, wxT("Add new songs"), wxDefaultPosition, wxDefaultSize, 0);
    actionsSizer->Add(addNewSongsButton, 0, wxALL, 5);
    addNewSongsButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        auto sdvxManager = this->chartManager.getSDVXManager();
        auto it = parsedSongs.begin();

        while(it != parsedSongs.end()) {
            if(it->songParseStatus != ParseStatus::NOT_FOUND) {
                it++;
                continue;
            }

            sdvxManager.addSong(*it, this->releaseInfo->release.id);
            it = parsedSongs.erase(it);
        }

        loadTreeData();
    });

    auto matchWithOtherReleaseButton = new wxButton(this, wxID_ANY, wxT("Match with other release"), wxDefaultPosition, wxDefaultSize, 0);
    actionsSizer->Add(matchWithOtherReleaseButton, 0, wxALL, 5);
    matchWithOtherReleaseButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
        std::optional<ReleaseInfo> otherReleaseInfo = std::nullopt;

        auto dialog = new wxDialog(this, wxID_ANY, wxT("Select Release"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
        auto panel = new ReleasePickerPanel(dialog, this->chartManager, otherReleaseInfo);
        auto sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(panel, 1, wxEXPAND, 5);
        dialog->SetSizer(sizer);
        dialog->Fit();
        dialog->ShowModal();

        if(otherReleaseInfo == std::nullopt) {
            return;
        }

        this->chartManager.getSDVXManager().checkSongs(parsedSongs, otherReleaseInfo->release.id);
        loadTreeData();
    });

    mainSizer->Add(actionsSizer, 0, wxEXPAND, 5);

    parsedDataTreeList = new wxTreeListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE);
    parsedDataTreeList->AppendColumn(wxT("Song"));
    parsedDataTreeList->AppendColumn(wxT("Song Status"));
    parsedDataTreeList->AppendColumn(wxT("Chart Status"));
    parsedDataTreeList->Bind(wxEVT_TREELIST_ITEM_CONTEXT_MENU, &SDVXParserPanel::onTreeItemRightClick, this);

    mainSizer->Add(parsedDataTreeList, 1, wxEXPAND | wxALL, 5);


    this->SetSizer(mainSizer);
    this->Layout();
}

void SDVXParserPanel::onFileChanged(wxFileDirPickerEvent& event) {
    if(releaseInfo == std::nullopt) {
        throw std::runtime_error("Release not set");
    }

    auto sdvxManager = chartManager.getSDVXManager();
    std::filesystem::path path = event.GetPath().ToStdString();
    parsedSongs = sdvxManager.parseMusicDb(path, releaseInfo->release.id);

    loadTreeData();
}

void SDVXParserPanel::onTreeItemRightClick(wxTreeListEvent& event) {
    auto id = event.GetItem().GetID();

    if(parsedSongsMap.contains(id)) {
        // Clicked on a song
        auto song = parsedSongsMap[id];
        auto menu = getSongContextMenu(song);
        parsedDataTreeList->PopupMenu(menu);
    }
    else {
        // Clicked on a chart
        auto parentId = parsedDataTreeList->GetItemParent(id).GetID();
        auto song = parsedSongsMap[parentId];
        auto chart = parsedChartsMap[id];
    }
}

wxMenu* SDVXParserPanel::getSongContextMenu(SDVXParsedSong* song) {
    auto menu = new wxMenu;
    menu->Append(wxID_ADD, wxT("Add song"));
    menu->Bind(wxEVT_MENU, [this, song](wxCommandEvent& event) {
        chartManager.getSDVXManager().addSong(*song, releaseInfo->release.id);
        auto removed = std::remove_if(parsedSongs.begin(), parsedSongs.end(), [song](SDVXParsedSong& s) {
            return s.internalId == song->internalId;
        });
        parsedSongs.erase(removed, parsedSongs.end());
        loadTreeData();
    }, wxID_ADD);

    return menu;
}

void SDVXParserPanel::loadTreeData() {
    parsedSongsMap.clear();
    parsedChartsMap.clear();

    wxTreeListItem root = parsedDataTreeList->GetRootItem();
    parsedDataTreeList->DeleteAllItems();

    for(auto& song : parsedSongs) {
        wxTreeListItem item = parsedDataTreeList->AppendItem(root, wxString::FromUTF8(song.artist + " - " + song.title));
        parsedSongsMap[item.GetID()] = &song;

        std::string songInfoText;
        std::string songChartInfoText;

        if(song.songParseStatus == ParseStatus::EXISTS) {
            songInfoText += "✅";
        }
        else {
            songInfoText += "❌";
        }

        songInfoText += '|';

        if(song.songEntryParseStatus == ParseStatus::EXISTS) {
            songInfoText += "✅";
        }
        else {
            songInfoText += "❌";
        }

        parsedDataTreeList->SetItemText(item, 1, wxString::FromUTF8(songInfoText));

        for(auto& chart : song.charts) {
            auto chartItem = parsedDataTreeList->AppendItem(item, SDVXManager::getDifficultyName(chart.difficulty, song.infiniteVersion) + ' ' + std::to_string(chart.level));
            parsedChartsMap[chartItem.GetID()] = &chart;

            std::string chartInfoText;

            if(chart.chartEntryParseStatus == ParseStatus::EXISTS) {
                chartInfoText += "✅";
                songChartInfoText += "✅";
            }
            else {
                chartInfoText += "❌";
                songChartInfoText += "❌";
            }

            parsedDataTreeList->SetItemText(chartItem, 2, wxString::FromUTF8(chartInfoText));
        }

        parsedDataTreeList->SetItemText(item, 2, wxString::FromUTF8(songChartInfoText));
    }
}
