//
// Created by Radio on 26/05/2024.
//

#ifndef BEMANIMETADATAPARSER_RELEASESERVICE_HPP
#define BEMANIMETADATAPARSER_RELEASESERVICE_HPP

#include <string>
#include <vector>
#include <tuple>
#include "BaseService.hpp"

class ReleaseService : public BaseService {
public:
    static void addRelease(std::uint32_t gameId, std::string&& code);
    std::vector<std::vector<std::string>> getAllData() override;

protected:
    std::string getTableName() override {return "game_release";}
};


#endif //BEMANIMETADATAPARSER_RELEASESERVICE_HPP
