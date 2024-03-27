//
// Created by pasca on 3/10/2024.
//

#include "../header/Player.h"
#include <cmath>
#include <string>
#include <iostream>
#include <utility>
#include <array>
#include <SFML/Window/Keyboard.hpp>

Player::Player(std::string name, unsigned int hp, float speed, float power): m_name(std::move(name)), m_hp(hp), m_speed(speed), m_power(power) {

    player_texture.loadFromFile("textures/Player.png");
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(640.0f, 640.0f);
    x = 0.f;
    y = 0.f;
}

/*Player::Player(const Player& other):m_name{other.m_name},m_hp{other.m_hp},m_speed{other.m_speed},m_power{other.m_power}{
    std::cout << "Player fost apelat" << '\n';
    x = 0;
    y = 0;
}///O sa o folosesc dar nu trec cu verde si ma enerveaza

Player&Player::operator=(const Player&other) {
    m_name = other.m_name;
    m_hp = other.m_hp;
    m_speed = other.m_speed;
    m_power = other.m_power;
    return *this;
}*/


std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player Name: " << player.m_name << ", HP: " << player.m_hp <<'\n';
    return os;
}

Player:: ~Player() {
    std::cout << "U got destructed"<< '\n';
}
void Player::handleInput() {

    float player_attack = m_power;
    std::cout<<player_attack;

    x = 0;
    y = 0;

}

void Player::update(const std::array<std::array<Cell, Map_height>,Map_width>& map) {

    std::array<bool, 4> walls{};
    walls[0] = wall_collision((unsigned short)(m_speed + player_sprite.getPosition().x), (unsigned short)player_sprite.getPosition().y, map);
    walls[1] = wall_collision((unsigned short)(player_sprite.getPosition().x), (unsigned short)(player_sprite.getPosition().y - m_speed), map);
    walls[2] = wall_collision((unsigned short)(player_sprite.getPosition().x - m_speed), (unsigned short)(player_sprite.getPosition().y), map);
    walls[3] = wall_collision((unsigned short)(player_sprite.getPosition().x), (unsigned short)(m_speed + player_sprite.getPosition().y), map);

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (0 == walls[0])
        {
            x += m_speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (0 == walls[1])
        {
            y -= m_speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (0 == walls[2])
        {
            x -= m_speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (0 == walls[3])
        {
            y += m_speed;
        }
    }


    player_sprite.move(x,y);
}


void Player::drawPlayer(sf::RenderWindow& window) {
    window.draw(player_sprite);


}

bool Player::wall_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>, Map_width> i_map) {

    bool output = false;

    float cell_x = float(i_x) / static_cast<float>(Cell_size);
    float cell_y = float(i_y) / static_cast<float>(Cell_size);

    for (unsigned char a = 0; a < 4; a++) {
        short x2 = 0;
        short y2 = 0;

        switch (a) {
            case 0: //Top left cell
            {
                x2 = static_cast<short>(std::floor(cell_x));
                y2 = static_cast<short>(std::floor(cell_y));

                break;
            }
            case 1: //Top right cell
            {
                x2 = static_cast<short>(std::ceil(cell_x));
                y2 = static_cast<short>(std::floor(cell_y));

                break;
            }
            case 2: //Bottom left cell
            {
                x2 = static_cast<short>(std::floor(cell_x));
                y2 = static_cast<short>(std::ceil(cell_y));

                break;
            }
            case 3: //Bottom right cell
            {
                x2 = static_cast<short>(std::ceil(cell_x));
                y2 = static_cast<short>(std::ceil(cell_y));
            }
            default:
                std::cout << "Nici perete";//Ma obliga tidy sa am si un default
        }

        //Check we are inside
        if (0 <= x2 && 0 <= y2 && Map_height > y2 && Map_width > x2) {
            if (Cell::Wall == i_map[x2][y2]) {
                output = true;
            }
        }
    }
    return output;
}


