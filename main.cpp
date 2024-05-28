#include "header/GameEngine.h"
#include "header/GameExceptions.h"
#include <iostream>

int main() {
    try {
        GameEngine gameEngine;
        gameEngine.run();
    } catch (const GameException& e) {
        std::cerr << "Game exception caught: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    ///un mic test sa vedem ca ne merg exceptiile
   /* try {
        Vampir vampir(100, 15, 2.0f, "non_existent_file.png");
    } catch (const TextureLoadException& e) {
        std::cerr << "Vampir exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }

    try {
        Skelet skelet(100, 10, 1.5f, "non_existent_file.png");
    } catch (const TextureLoadException& e) {
        std::cerr << "Skelet exception caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Standard exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }*/
}
