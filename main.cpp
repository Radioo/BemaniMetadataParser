#include <iostream>
#include "ChartManagerConfig.hpp"
#include "ChartManager.hpp"

int main() {
    try {
        auto manager = ChartManager({"/path/to/series.csv"});
        auto gameManager = manager.getGameManager();
        gameManager.addSeries("SOUND VOLTEX");
        auto series = gameManager.getSeries();

        std::cout << "Series\n";
        for (const auto& [id, name] : series) {
            std::cout << id << " " << name << "\n";
        }

        gameManager.addGame(0, "SOUND VOLTEX EXCEED GEAR", 6);
        auto games = gameManager.getGames();

        std::cout << "Games\n";
        for (const auto& game : games) {
            std::cout << game.id << " " << game.name << " (" << std::to_string(game.version) << ")" "\n";
        }

        gameManager.addRelease(0, "2024060400");
        auto releases = gameManager.getReleases();

        std::cout << "Releases\n";
        for (const auto& release : releases) {
            std::cout << release.id << " " << release.code << "\n";
        }

        auto sdvxManager = manager.getSDVXManager();
        std::filesystem::path path = R"(F:\SDVX\SDVX 6 - EXCEED GEAR\data\others\music_db.xml)";
        auto songs = sdvxManager.parseMusicDb(path);

        for(const auto& song : songs) {
            std::cout << song.title << " by " << song.artist << "\n";
            for(const auto& chart : song.charts) {
                std::cout << "  " << static_cast<int>(chart.difficulty) << " " << static_cast<int>(chart.level) << " " << static_cast<int>(chart.limited) << " " << chart.maxExScore << "\n";
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "An error occurred" << std::endl;
    }
}