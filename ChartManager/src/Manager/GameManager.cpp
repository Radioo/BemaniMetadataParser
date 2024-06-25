//
// Created by Radio on 07/06/2024.
//

#include <csv.hpp>
#include <filesystem>

#include "../include/Manager/GameManager.hpp"
#include "../Util/DbUtil.hpp"

GameManager::GameManager(std::filesystem::path& seriesCsvPath) : seriesCsvPath(seriesCsvPath) {
    this->loadData();
}

void GameManager::loadData() {
//    this->series = this->csvUtil.deserialize<Series>(this->seriesCsvPath);
}

void GameManager::addSeries(std::string& name) {
    auto query = DBUtil::prepare("INSERT INTO series (name) VALUES (?)");
    query.bind(1, name);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to insert series");
    }
}

std::vector<Series> GameManager::getSeries() {
    auto countQuery = DBUtil::prepare("SELECT COUNT(*) FROM series");
    countQuery.executeStep();
    auto count = countQuery.getColumn(0).getInt();

    auto seriesQuery = DBUtil::prepare("SELECT * FROM series");
    std::vector<Series> series(count);

    std::uint32_t i = 0;
    while(seriesQuery.executeStep()) {
        series[i++] = {
                seriesQuery.getColumn(0).getUInt(),
                seriesQuery.getColumn(1).getString()
        };
    }

    return series;
}

void GameManager::addGame(std::uint32_t seriesId, std::string& name, std::uint8_t version) {
    auto query = DBUtil::prepare("INSERT INTO game (series_id, name, version) VALUES (?, ?, ?)");
    query.bind(1, seriesId);
    query.bind(2, name);
    query.bind(3, version);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to insert game");
    }
}

std::vector<Game> GameManager::getGames() {
    auto countQuery = DBUtil::prepare("SELECT COUNT(*) FROM game");
    countQuery.executeStep();
    auto count = countQuery.getColumn(0).getInt();

    auto gameQuery = DBUtil::prepare("SELECT * FROM game");
    std::vector<Game> games(count);

    std::uint32_t i = 0;
    while(gameQuery.executeStep()) {
        games[i++] = {
            gameQuery.getColumn(0).getUInt(),
            gameQuery.getColumn(1).getUInt(),
            gameQuery.getColumn(2).getString(),
            static_cast<uint8_t>(gameQuery.getColumn(3).getUInt())
        };
    }

    return games;
}

void GameManager::addRelease(std::uint32_t gameId, std::string&& code) {
    auto query = DBUtil::prepare("INSERT INTO release (game_id, code) VALUES (?, ?)");
    query.bind(1, gameId);
    query.bind(2, code);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to insert release");
    }
}

std::vector<Release> GameManager::getReleases() {
    auto countQuery = DBUtil::prepare("SELECT COUNT(*) FROM release");
    countQuery.executeStep();
    auto count = countQuery.getColumn(0).getInt();

    auto releaseQuery = DBUtil::prepare("SELECT * FROM release");
    std::vector<Release> releases(count);

    std::uint32_t i = 0;
    while(releaseQuery.executeStep()) {
        releases[i++] = {
            releaseQuery.getColumn(0).getUInt(),
            releaseQuery.getColumn(1).getUInt(),
            releaseQuery.getColumn(2).getString()
        };
    }

    return releases;
}

Series GameManager::getSeries(std::uint32_t id) {
    auto query = DBUtil::prepare("SELECT * FROM series WHERE id = ?");
    query.bind(1, id);
    auto result = query.executeStep();

    if(!result) {
        throw std::runtime_error("Series with id " + std::to_string(id) + " not found");
    }

    return {
        query.getColumn(0).getUInt(),
        query.getColumn(1).getString()
    };
}

void GameManager::updateSeries(Series& series) {
    auto query = DBUtil::prepare("UPDATE series SET name = ? WHERE id = ?");
    query.bind(1, series.name);
    query.bind(2, series.id);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to update series");
    }
}

void GameManager::deleteSeries(std::uint32_t id) {
    auto query = DBUtil::prepare("DELETE FROM series WHERE id = ?");
    query.bind(1, id);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to delete series");
    }
}

Game GameManager::getGame(std::uint32_t id) {
    auto query = DBUtil::prepare("SELECT * FROM game WHERE id = ?");
    query.bind(1, id);
    auto result = query.executeStep();

    if(!result) {
        throw std::runtime_error("Game with id " + std::to_string(id) + " not found");
    }

    return {
        query.getColumn(0).getUInt(),
        query.getColumn(1).getUInt(),
        query.getColumn(2).getString(),
        static_cast<std::uint8_t>(query.getColumn(3).getUInt())
    };
}

void GameManager::deleteGame(std::uint32_t id) {
    auto query = DBUtil::prepare("DELETE FROM game WHERE id = ?");
    query.bind(1, id);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to delete game");
    }
}

void GameManager::updateGame(Game& game) {
    auto query = DBUtil::prepare("UPDATE game SET series_id = ?, name = ?, version = ? WHERE id = ?");
    query.bind(1, game.seriesId);
    query.bind(2, game.name);
    query.bind(3, game.version);
    query.bind(4, game.id);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to update game");
    }
}
