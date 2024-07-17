// GameEngine.h

#ifndef OOP_GAMEENGINE_H
#define OOP_GAMEENGINE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Map.h"
#include "Chapter1.h"
#include "Chapter2.h"
#include "GameExceptions.h"

class GameEngine {

public:
    static GameEngine& getInstance();

    void run();

    friend std::ostream& operator<<(std::ostream& os, const GameEngine& gameEngine);

    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

    ~GameEngine();

private:
    GameEngine();

    void processEvents();
    void update(sf::Time dt);
    void render();

    bool is_render;

    sf::RenderWindow window;

    Chapter1 ch1;
    Chapter2 ch2;

    sf::Texture end_screen_texture;
    sf::Texture win_screen_texture;
    sf::Sprite end_screen;
    sf::Sprite win_screen;

    sf::Clock clock;
};

#endif //OOP_GAMEENGINE_H
