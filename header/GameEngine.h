//
// Created by pasca on 4/2/2024.
//

#ifndef OOP_GAMEENGINE_H
#define OOP_GAMEENGINE_H


#include <SFML/Window/Event.hpp>
#include "Bat.h"
#include "Map.h"
#include "Chapter1.h"

class GameEngine {

public:

    GameEngine();
    void run();

    friend std::ostream& operator<<(std::ostream& os, const GameEngine& gameEngine);
    ~GameEngine();

private:

    void processEvents();
    void update();
    void render();

    bool is_render;

    sf::RenderWindow window;

    Chapter1 ch1;

    sf::Texture end_screen_texture;
    sf::Texture win_screen_texture;
    sf::Sprite end_screen;
    sf::Sprite win_screen;

};


#endif //OOP_GAMEENGINE_H
