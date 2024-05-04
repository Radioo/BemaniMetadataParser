//
// Created by Radio on 04/05/2024.
//

#ifndef BEMANIMETADATAPARSER_DB_HPP
#define BEMANIMETADATAPARSER_DB_HPP

#include <unordered_map>
#include <cstdint>
#include "Model/Game/Series.hpp"
#include "Model/Game/Game.hpp"
#include "Model/Game/GameRelease.hpp"
#include "Model/SDVX/SdvxSong.hpp"
#include "Model/SDVX/SdvxChart.hpp"
#include "Model/SDVX/SdvxSongEntry.hpp"
#include "Model/SDVX/SdvxChartEntry.hpp"

class DB {
private:
    std::unordered_map<std::uint32_t, Series> series;
    std::unordered_map<std::uint32_t, Game> game;
    std::unordered_map<std::uint32_t, GameRelease> game_release;

    std::unordered_map<std::uint32_t, SdvxSong> sdvx_song;
    std::unordered_map<std::uint32_t, SdvxChart> sdvx_chart;
    std::unordered_map<std::uint32_t, SdvxSongEntry> sdvx_song_entry;
    std::unordered_map<std::uint32_t, SdvxChartEntry> sdvx_chart_entry;
};


#endif //BEMANIMETADATAPARSER_DB_HPP
