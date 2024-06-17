//
// Created by Radio on 16/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXDIFFICULTY_HPP
#define BEMANIMETADATAPARSER_SDVXDIFFICULTY_HPP

#include <cstdint>

enum class SDVXDifficulty : std::uint8_t {
    NOVICE = 0,
    ADVANCED = 1,
    EXHAUST = 2,
    INFINITE = 3,
    MAXIMUM = 4,
};

#endif //BEMANIMETADATAPARSER_SDVXDIFFICULTY_HPP
