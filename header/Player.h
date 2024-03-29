//
// Created by pasca on 3/11/2024.
//

#pragma once
#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <array>
#include "Global.h"

class Player{
public:
    ///Constructor
    explicit Player(std::string  name = "Default", unsigned int hp = 100,float speed = 1.f, float power = 1.0f);

    ///Copy
    //Player(const Player& other); O sa il folosesc dar vreau sa am totul cu verde
    //Player& operator=(const Player& other);///

    ///Other
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    void handleInput();
    void update(const std::array<std::array<Cell, Map_height>,Map_width>& map);
    void drawPlayer(sf::RenderWindow& window);
    static bool wall_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>,Map_width> i_map);

    ///Destroy(Mosh Pit)
    ~Player();

private:
    std::string m_name;
    unsigned int m_hp;
    float m_speed;
    float m_power;
    sf::Sprite player_sprite;
    sf::Texture player_texture;
    sf::RectangleShape playerShape;
    float x,y;
};


#endif //OOP_PLAYER_H