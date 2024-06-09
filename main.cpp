#include <iostream>
#include "ChartManagerConfig.hpp"
#include "ChartManager.hpp"

int main() {
    auto manager = ChartManager({"/path/to/series.csv"});
    auto gameManager = manager.getGameManager();
    auto series = gameManager.getSeries();

    for (const auto& [key, value] : series) {
        std::cout << "Key: " << key << std::endl;
    }
}