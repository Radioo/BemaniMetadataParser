//
// Created by Radio on 23/05/2024.
//

#ifndef BEMANIMETADATAPARSER_BASESERVICE_HPP
#define BEMANIMETADATAPARSER_BASESERVICE_HPP

#include <vector>
#include <string>

class BaseService {
public:
    std::vector<std::string> getColumns();
    std::vector<std::vector<std::string>> getAllData();

protected:
    virtual std::string getTableName() = 0;
};


#endif //BEMANIMETADATAPARSER_BASESERVICE_HPP
