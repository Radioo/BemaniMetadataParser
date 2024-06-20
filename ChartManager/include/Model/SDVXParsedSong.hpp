//
// Created by Radio on 16/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXPARSEDSONG_HPP
#define BEMANIMETADATAPARSER_SDVXPARSEDSONG_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <optional>

#include "SDVXParsedChart.hpp"
#include "SDVXSong.hpp"
#include "../Enum/ParseStatus.hpp"

struct SDVXParsedSong {
    std::optional<ParseStatus> songParseStatus;
    std::optional<ParseStatus> songEntryParseStatus;

    std::string title;
    std::string artist;
    std::uint32_t internalId;
    std::uint8_t infiniteVersion;
    std::vector<SDVXParsedChart> charts;
};

#endif //BEMANIMETADATAPARSER_SDVXPARSEDSONG_HPP
