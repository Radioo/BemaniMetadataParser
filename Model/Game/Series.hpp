//
// Created by Radio on 03/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SERIES_HPP
#define BEMANIMETADATAPARSER_SERIES_HPP

#include <cstdint>
#include <string>

class Series {
    std::uint32_t id;
    std::string name;

    Series(
            std::uint32_t id,
            std::string name
            ) :
            id(id),
            name(std::move(name)) {}
};


#endif //BEMANIMETADATAPARSER_SERIES_HPP
