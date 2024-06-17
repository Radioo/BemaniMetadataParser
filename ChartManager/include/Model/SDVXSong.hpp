//
// Created by Radio on 13/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXSONG_HPP
#define BEMANIMETADATAPARSER_SDVXSONG_HPP

#include <cstdint>
#include <string>

struct SDVXSong {
    std::uint32_t id;
    std::uint32_t releaseId;
    std::string title;
    std::string artist;
};

#endif //BEMANIMETADATAPARSER_SDVXSONG_HPP
