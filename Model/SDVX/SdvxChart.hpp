//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXCHART_HPP
#define BEMANIMETADATAPARSER_SDVXCHART_HPP

#include <cstdint>
#include <optional>

class SdvxChart {
    std::uint32_t id;
    std::uint32_t sdvxSongId;
    std::optional<std::uint32_t> maxExScore;

    SdvxChart(
            std::uint32_t id,
            std::uint32_t sdvxSongId,
            std::optional<std::uint32_t> maxExScore
            ) :
            id(id),
            sdvxSongId(sdvxSongId),
            maxExScore(maxExScore) {}
};


#endif //BEMANIMETADATAPARSER_SDVXCHART_HPP
