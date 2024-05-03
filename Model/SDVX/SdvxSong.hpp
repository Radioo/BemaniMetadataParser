//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXSONG_HPP
#define BEMANIMETADATAPARSER_SDVXSONG_HPP

#include <cstdint>
#include <string>
#include <optional>

class SdvxSong {
    std::uint32_t id;
    std::string title;
    std::string artist;
    std::optional<std::uint8_t> infiniteVersion;

    SdvxSong(
            std::uint32_t id,
            std::string title,
            std::string artist,
            std::optional<std::uint8_t> infiniteVersion
            ) :
            id(id),
            title(std::move(title)),
            artist(std::move(artist)),
            infiniteVersion(infiniteVersion) {}
};


#endif //BEMANIMETADATAPARSER_SDVXSONG_HPP
