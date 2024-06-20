//
// Created by Radio on 14/06/2024.
//

#include <stdexcept>
#include <pugixml.hpp>

#include "../../include/Manager/SDVXManager.hpp"
#include "../Util/FileUtil.hpp"
#include "../Util/EncodingUtil.hpp"
#include "../Util/DbUtil.hpp"

SDVXDifficulty SDVXManager::getDifficultyFromXml(std::string&& difficulty) {
    if(difficulty == "novice") {
        return SDVXDifficulty::NOVICE;
    }
    if(difficulty == "advanced") {
        return SDVXDifficulty::ADVANCED;
    }
    if(difficulty == "exhaust") {
        return SDVXDifficulty::EXHAUST;
    }
    if(difficulty == "infinite") {
        return SDVXDifficulty::INFINITE;
    }
    if(difficulty == "maximum") {
        return SDVXDifficulty::MAXIMUM;
    }

    throw std::invalid_argument("Invalid difficulty " + difficulty);
}

std::vector<SDVXParsedSong> SDVXManager::parseMusicDb(std::filesystem::path& musicDbPath, std::uint32_t releaseId) {
    auto xmlString = FileUtil::readFileIntoString(musicDbPath);
    xmlString = EncodingUtil::convertSDVXMusicDbToUtf8(xmlString);
    pugi::xml_document doc;
    doc.load_string(xmlString.c_str());

    std::vector<SDVXParsedSong> output;

    auto mdbNode = doc.child("mdb");
    for(const auto& musicNode : mdbNode.children("music")) {
        std::vector<SDVXParsedChart> charts;

        for(const auto& difficultyNode : musicNode.child("difficulty").children()) {
            auto difficulty = getDifficultyFromXml(difficultyNode.name());
            auto level = static_cast<std::uint8_t>(difficultyNode.child("difnum").text().as_uint());
            if(level == 0) {
                continue;
            }

            charts.push_back({
                .chartParseStatus = std::nullopt,
                .chartEntryParseStatus = std::nullopt,
                .difficulty = difficulty,
                .level = level,
                .limited = static_cast<std::uint8_t>(difficultyNode.child("limited").text().as_uint()),
                .maxExScore = difficultyNode.child("max_exscore").text().as_uint()
            });
        }

        auto infoNode = musicNode.child("info");
        output.push_back({
            .songParseStatus = std::nullopt,
            .songEntryParseStatus = std::nullopt,
            .title = infoNode.child("title_name").text().as_string(),
            .artist = infoNode.child("artist_name").text().as_string(),
            .internalId = musicNode.attribute("id").as_uint(),
            .infiniteVersion = static_cast<std::uint8_t>(infoNode.child("inf_ver").text().as_uint()),
            .charts = charts
        });
    }

    return output;
}
