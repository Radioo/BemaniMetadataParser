//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXSONGENTRY_HPP
#define BEMANIMETADATAPARSER_SDVXSONGENTRY_HPP

#include <cstdint>

class SdvxSongEntry {
    std::uint32_t id;
    std::uint32_t gameReleaseId;
    std::uint32_t sdvxSongId;
    std::uint32_t internalId;

    SdvxSongEntry(
            std::uint32_t id,
            std::uint32_t gameReleaseId,
            std::uint32_t sdvxSongId,
            std::uint32_t internalId
            ) :
            id(id),
            gameReleaseId(gameReleaseId),
            sdvxSongId(sdvxSongId),
            internalId(internalId) {}
};


#endif //BEMANIMETADATAPARSER_SDVXSONGENTRY_HPP
