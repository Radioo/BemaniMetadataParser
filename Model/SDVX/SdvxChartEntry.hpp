//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXCHARTENTRY_HPP
#define BEMANIMETADATAPARSER_SDVXCHARTENTRY_HPP

#include <cstdint>

class SdvxChartEntry {
    std::uint32_t id;
    std::uint32_t sdvxChartId;
    std::uint32_t sdvxSongEntryId;
    std::uint8_t difficulty;
    std::uint8_t level;
    std::uint8_t limited;

    SdvxChartEntry(
            std::uint32_t id,
            std::uint32_t sdvxChartId,
            std::uint32_t sdvxSongEntryId,
            std::uint8_t difficulty,
            std::uint8_t level,
            std::uint8_t limited
            ) :
            id(id),
            sdvxChartId(sdvxChartId),
            sdvxSongEntryId(sdvxSongEntryId),
            difficulty(difficulty),
            level(level),
            limited(limited) {}
};


#endif //BEMANIMETADATAPARSER_SDVXCHARTENTRY_HPP
