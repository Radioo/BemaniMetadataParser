//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_GAMERELEASE_HPP
#define BEMANIMETADATAPARSER_GAMERELEASE_HPP

#include <cstdint>
#include <string>

class GameRelease {
    std::uint32_t id;
    std::uint32_t gameId;
    std::string code;

    GameRelease(
            std::uint32_t id,
            std::uint32_t gameId,
            std::string code
            ) :
            id(id),
            gameId(gameId),
            code(std::move(code)) {}
};


#endif //BEMANIMETADATAPARSER_GAMERELEASE_HPP
