//
// Created by Radio on 10/05/2024.
//

#ifndef BEMANIMETADATAPARSER_PARSER_HPP
#define BEMANIMETADATAPARSER_PARSER_HPP


#include "Services/SeriesService.hpp"
#include <functional>
#include <cstdint>

class Parser {
public:
    Parser();

    SeriesService seriesService = SeriesService();

    static void commit();
    static void initialize();
    static void setAfterCommitCallback(std::function<void()> callback);
    static void setOnUncommitedChangesChangeCallback(std::function<void()> callback);
    static std::uint64_t getUncommitedChanges();
};


#endif //BEMANIMETADATAPARSER_PARSER_HPP
