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
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "An error occurred" << std::endl;
    }
}