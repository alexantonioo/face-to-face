#include <SFML/Graphics.hpp>
#include "Boxer.hpp"
#include "Ring.hpp"
#include "Game.hpp"
#include <filesystem>
#include <iostream>

int main() {

    /*for (const auto &entry : std::filesystem::directory_iterator("assets/images")) {
        std::cout << entry.path() << std::endl;
    }*/
    Game game;
    game.run();

    return 0;
}

