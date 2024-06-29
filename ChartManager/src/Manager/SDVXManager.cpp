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
        auto title = std::string(infoNode.child("title_name").text().as_string());
        auto artist = std::string(infoNode.child("artist_name").text().as_string());
        output.push_back({
            .songParseStatus = std::nullopt,
            .songEntryParseStatus = std::nullopt,
            .title = title,
            .artist = artist,
            .internalId = musicNode.attribute("id").as_uint(),
            .infiniteVersion = static_cast<std::uint8_t>(infoNode.child("inf_ver").text().as_uint()),
            .charts = charts
        });
    }

    checkSongs(output, releaseId);
    return output;
}

const std::string& SDVXManager::getDifficultyName(SDVXDifficulty difficulty, std::uint8_t infiniteVersion) {
    switch(difficulty) {
        case SDVXDifficulty::NOVICE:
            return DIFFICULTY_NOVICE;
        case SDVXDifficulty::ADVANCED:
            return DIFFICULTY_ADVANCED;
        case SDVXDifficulty::EXHAUST:
            return DIFFICULTY_EXHAUST;
        case SDVXDifficulty::INFINITE:
            switch(infiniteVersion) {
                case 2:
                    return DIFFICULTY_INFINITE;
                case 3:
                    return DIFFICULTY_GRAVITY;
                case 4:
                    return DIFFICULTY_HEAVENLY;
                case 5:
                    return DIFFICULTY_VIVID;
                case 6:
                    return DIFFICULTY_EXCEED;
                default:
                    throw std::invalid_argument("Invalid infinite version " + std::to_string(infiniteVersion));
            }
        case SDVXDifficulty::MAXIMUM:
            return DIFFICULTY_MAXIMUM;
    }

    throw std::invalid_argument("Invalid difficulty " + std::to_string(static_cast<std::uint8_t>(difficulty)));
}

void SDVXManager::addSong(SDVXParsedSong& song, std::uint32_t releaseId) {
    auto& db = DBUtil::getDb();
    auto transaction = SQLite::Transaction(db);

    try {
        auto songInsertQuery = SQLite::Statement(db, "INSERT INTO sdvx_song (title, artist) VALUES (?, ?);");
        songInsertQuery.bind(1, song.title);
        songInsertQuery.bind(2, song.artist);
        songInsertQuery.exec();
        auto songId = db.getLastInsertRowid();

        auto songEntryInsertQuery = SQLite::Statement(db, "INSERT INTO sdvx_song_entry (sdvx_song_id, internal_id, infinite_version) VALUES (?, ?, ?);");
        songEntryInsertQuery.bind(1, songId);
        songEntryInsertQuery.bind(2, song.internalId);
        songEntryInsertQuery.bind(3, song.infiniteVersion);
        songEntryInsertQuery.exec();
        auto songEntryId = db.getLastInsertRowid();

        auto songEntryReleaseInsertQuery = SQLite::Statement(db, "INSERT INTO sdvx_song_entry_release (release_id, sdvx_song_entry_id) VALUES (?, ?);");
        songEntryReleaseInsertQuery.bind(1, releaseId);
        songEntryReleaseInsertQuery.bind(2, songEntryId);
        songEntryReleaseInsertQuery.exec();

        for(const auto& chart : song.charts) {
            auto chartInsertQuery = SQLite::Statement(db, "INSERT INTO sdvx_chart (sdvx_song_id) VALUES (?);");
            chartInsertQuery.bind(1, songId);
            chartInsertQuery.exec();
            auto chartId = db.getLastInsertRowid();

            auto chartEntryInsertQuery = SQLite::Statement(db, "INSERT INTO sdvx_chart_entry (sdvx_chart_id, difficulty, level, limited, max_ex_score) VALUES (?, ?, ?, ?, ?);");
            chartEntryInsertQuery.bind(1, chartId);
            chartEntryInsertQuery.bind(2, static_cast<std::uint8_t>(chart.difficulty));
            chartEntryInsertQuery.bind(3, chart.level);
            chartEntryInsertQuery.bind(4, chart.limited);
            chartEntryInsertQuery.bind(5, chart.maxExScore);
            chartEntryInsertQuery.exec();
            auto chartEntryId = db.getLastInsertRowid();

            auto chartEntryReleaseInsertQuery = SQLite::Statement(db, "INSERT INTO sdvx_chart_entry_release (release_id, sdvx_chart_entry_id) VALUES (?, ?);");
            chartEntryReleaseInsertQuery.bind(1, releaseId);
            chartEntryReleaseInsertQuery.bind(2, chartEntryId);
            chartEntryReleaseInsertQuery.exec();
        }

        transaction.commit();
    }
    catch(const std::exception& e) {
        transaction.rollback();
        throw e;
    }
    catch(...) {
        transaction.rollback();
        throw std::runtime_error("Unknown while adding SDVX song");
    }
}

void SDVXManager::checkSongs(std::vector<SDVXParsedSong>& songs, std::uint32_t releaseId) {
    for(auto& song : songs) {
        auto songQuery = DBUtil::prepare("SELECT * FROM sdvx_song WHERE title = ? AND artist = ?;");
        songQuery.bind(1, song.title);
        songQuery.bind(2, song.artist);
        if(songQuery.executeStep()) {
            song.songParseStatus = ParseStatus::EXISTS;

            auto songId = songQuery.getColumn("id").getInt();

            auto songEntryQuery = DBUtil::prepare(R"(
                SELECT *
                FROM sdvx_song_entry
                JOIN sdvx_song_entry_release ON sdvx_song_entry.id = sdvx_song_entry_release.sdvx_song_entry_id
                WHERE
                    sdvx_song_entry.sdvx_song_id = ? AND
                    sdvx_song_entry.internal_id = ? AND
                    sdvx_song_entry.infinite_version = ? AND
                    sdvx_song_entry_release.release_id = ?;
            )");
            songEntryQuery.bind(1, songId);
            songEntryQuery.bind(2, song.internalId);
            songEntryQuery.bind(3, song.infiniteVersion);
            songEntryQuery.bind(4, releaseId);
            if(songEntryQuery.executeStep()) {
                song.songEntryParseStatus = ParseStatus::EXISTS;
            }
            else {
                song.songEntryParseStatus = ParseStatus::NOT_FOUND;
            }

            for(auto& chart : song.charts) {
                auto chartEntryQuery = DBUtil::prepare(R"(
                    SELECT *
                    FROM sdvx_chart_entry
                    JOIN sdvx_chart ON sdvx_chart_entry.sdvx_chart_id = sdvx_chart.id
                    JOIN sdvx_song ON sdvx_chart.sdvx_song_id = sdvx_song.id
                    JOIN sdvx_chart_entry_release ON sdvx_chart_entry.id = sdvx_chart_entry_release.sdvx_chart_entry_id
                    WHERE
                        sdvx_song.id = ? AND
                        sdvx_chart_entry_release.release_id = ? AND
                        sdvx_chart_entry.difficulty = ? AND
                        sdvx_chart_entry.level = ? AND
                        sdvx_chart_entry.limited = ? AND
                        sdvx_chart_entry.max_ex_score = ?;
                )");
                chartEntryQuery.bind(1, songId);
                chartEntryQuery.bind(2, releaseId);
                chartEntryQuery.bind(3, static_cast<std::uint8_t>(chart.difficulty));
                chartEntryQuery.bind(4, chart.level);
                chartEntryQuery.bind(5, chart.limited);
                chartEntryQuery.bind(6, chart.maxExScore);
                if(chartEntryQuery.executeStep()) {
                    chart.chartEntryParseStatus = ParseStatus::EXISTS;
                }
            }
        }
        else {
            song.songParseStatus = ParseStatus::NOT_FOUND;
        }
    }
}
