//
// Created by Radio on 19/05/2024.
//

#ifndef BEMANIMETADATAPARSER_SERIESSERVICE_HPP
#define BEMANIMETADATAPARSER_SERIESSERVICE_HPP

#include <string>
#include <vector>
#include <tuple>
#include "BaseService.hpp"

class SeriesService : public BaseService {
public:
    static void addSeries(std::string&& name);
    static std::vector<std::tuple<std::uint32_t, std::string>> getSeries();

protected:
    std::string getTableName() override {return "series";}
};


#endif //BEMANIMETADATAPARSER_SERIESSERVICE_HPP
