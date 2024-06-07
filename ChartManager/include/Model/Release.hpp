//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_RELEASE_HPP
#define BEMANIMETADATAPARSER_RELEASE_HPP

#include <cstdint>
#include <string>

struct Release {
    std::uint32_t id;
    std::uint32_t gameId;
    std::string code;
};

#endif //BEMANIMETADATAPARSER_RELEASE_HPP
