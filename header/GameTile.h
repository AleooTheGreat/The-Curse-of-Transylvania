//
// Created by pasca on 3/13/2024.
//

#ifndef OOP_GAMETILE_H
#define OOP_GAMETILE_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameTile {

public:
    GameTile(const std::string&, float, float, bool, bool);
    bool setUpSprite(const std::string&);
    bool isFree;
    bool isExit;
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
};


#endif //OOP_GAMETILE_H
