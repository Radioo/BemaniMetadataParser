//
// Created by Radio on 16/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXPARSEDCHART_HPP
#define BEMANIMETADATAPARSER_SDVXPARSEDCHART_HPP

#include <cstdint>
#include <optional>

#include "../Enum/SDVXDifficulty.hpp"
#include "../Enum/ParseStatus.hpp"

struct SDVXParsedChart {
    std::optional<ParseStatus> chartParseStatus;
    std::optional<ParseStatus> chartEntryParseStatus;

    SDVXDifficulty difficulty;
    std::uint8_t level;
    std::uint8_t limited;
    std::uint32_t maxExScore;
};

#endif //BEMANIMETADATAPARSER_SDVXPARSEDCHART_HPP
