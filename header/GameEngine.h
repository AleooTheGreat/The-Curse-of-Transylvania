//
// Created by pasca on 4/2/2024.
//

#ifndef OOP_GAMEENGINE_H
#define OOP_GAMEENGINE_H


#include <SFML/Window/Event.hpp>
#include "Bat.h"
#include "Map.h"

class GameEngine {

public:
    GameEngine();
    void run();
private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Player player;
    Map map;
    Bat bat1;
    sf::Texture end_screen_texture;
    sf::Sprite end_screen;
};


#endif //OOP_GAMEENGINE_H
