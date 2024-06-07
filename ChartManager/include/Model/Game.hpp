//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_GAME_HPP
#define BEMANIMETADATAPARSER_GAME_HPP

#include <cstdint>
#include <string>

struct Game {
    std::uint32_t id;
    std::uint32_t seriesId;
    std::string name;
    std::uint8_t version;
};

#endif //BEMANIMETADATAPARSER_GAME_HPP
