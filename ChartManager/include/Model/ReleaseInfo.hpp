//
// Created by Radio on 26/06/2024.
//

#ifndef BEMANIMETADATAPARSER_RELEASEINFO_HPP
#define BEMANIMETADATAPARSER_RELEASEINFO_HPP

#include "Series.hpp"
#include "Game.hpp"
#include "Release.hpp"

struct ReleaseInfo {
    Series series;
    Game game;
    Release release;
};

#endif //BEMANIMETADATAPARSER_RELEASEINFO_HPP
