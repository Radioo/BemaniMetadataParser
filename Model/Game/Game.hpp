//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_GAME_HPP
#define BEMANIMETADATAPARSER_GAME_HPP

#include <cstdint>
#include <string>

class Game {
    std::uint32_t id;
    std::uint32_t seriesId;
    std::string name;
    std::uint8_t version;

    Game(
            std::uint32_t id,
            std::uint32_t seriesId,
            std::string name,
            std::uint8_t version
            ) :
            id(id),
            seriesId(seriesId),
            name(std::move(name)),
            version(version) {}
};


#endif //BEMANIMETADATAPARSER_GAME_HPP
