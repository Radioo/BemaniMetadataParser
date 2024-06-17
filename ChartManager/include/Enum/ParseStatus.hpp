//
// Created by Radio on 17/06/2024.
//

#ifndef BEMANIMETADATAPARSER_PARSESTATUS_HPP
#define BEMANIMETADATAPARSER_PARSESTATUS_HPP

#include <cstdint>

enum class ParseStatus : std::uint8_t {
    EXISTS,
    DOES_NOT_EXIST,
    MODIFIED,
};

#endif //BEMANIMETADATAPARSER_PARSESTATUS_HPP
