#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "header/Player.h"
#include "header/Map.h"
#include "header/Bat.h"
#include "header/GameEngine.h"


int main() {

    GameEngine gameEngine;
    gameEngine.run();
    return 0;
}
