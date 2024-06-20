//
// Created by Radio on 19/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXSONGENTRY_HPP
#define BEMANIMETADATAPARSER_SDVXSONGENTRY_HPP

#include <cstdint>

struct SDVXSongEntry {
    std::uint32_t id;
    std::uint32_t sdvxSongId;
    std::uint32_t releaseId;
    std::uint32_t internalId;
    std::uint8_t infiniteVersion;
};

#endif //BEMANIMETADATAPARSER_SDVXSONGENTRY_HPP
