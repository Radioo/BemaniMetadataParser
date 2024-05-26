//
// Created by Radio on 26/05/2024.
//

#ifndef BEMANIMETADATAPARSER_GAMESERVICE_HPP
#define BEMANIMETADATAPARSER_GAMESERVICE_HPP

#include <string>
#include "BaseService.hpp"

class GameService : public BaseService {
public:
    static void addGame(std::uint32_t seriesId, std::string&& name, std::uint32_t version);
    std::vector<std::vector<std::string>> getAllData() override;

protected:
    std::string getTableName() override {return "game";}
};


#endif //BEMANIMETADATAPARSER_GAMESERVICE_HPP
