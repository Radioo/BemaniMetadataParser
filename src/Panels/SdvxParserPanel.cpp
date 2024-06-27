//
// Created by Radio on 26/06/2024.
//

#include "SdvxParserPanel.hpp"

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

    parsedDataTreeList = new wxTreeListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTL_DEFAULT_STYLE);
    parsedDataTreeList->AppendColumn(wxT("Song"));
    parsedDataTreeList->AppendColumn(wxT("Info"));
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
        auto removed = std::remove_if(parsedSongs.begin(), parsedSongs.end(), [song](SDVXParsedSong& s) {
            return s.internalId == song->internalId;
        });
        parsedSongs.erase(removed, parsedSongs.end());
        loadTreeData();
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

        std::string infoText;

        if(song.songParseStatus == ParseStatus::MATCHED) {
            infoText += "Song: ✅";
        }

        if(song.songEntryParseStatus == ParseStatus::MATCHED) {
            infoText += " Song Entry: ✅";
        }

        parsedDataTreeList->SetItemText(item, 1, wxString::FromUTF8(infoText));

        for(auto& chart : song.charts) {
            auto chartItem = parsedDataTreeList->AppendItem(item, SDVXManager::getDifficultyName(chart.difficulty, song.infiniteVersion) + ' ' + std::to_string(chart.level));
            parsedChartsMap[chartItem.GetID()] = &chart;
        }
    }
}
