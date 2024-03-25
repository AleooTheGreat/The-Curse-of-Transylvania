//
// Created by pasca on 3/10/2024.
//

#include "../header/Player.h"
#include <string>
#include <iostream>
#include <utility>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

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
}*////O sa o folosesc dar nu trec cu verde si ma enerveaza

Player&Player::operator=(const Player&other) {
    m_name = other.m_name;
    m_hp = other.m_hp;
    m_speed = other.m_speed;
    m_power = other.m_power;
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player Name: " << player.m_name << ", HP: " << player.m_hp <<'\n';
    return os;
}

Player:: ~Player() {
    std::cout << "U got destructed"<< '\n';
}
void Player::handleInput() {

    x = 0;
    y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        x -= m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        x += m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        y += m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        y -= m_speed;
    }

}

void Player::update(std::vector<std::vector<int>>& map) {

    int left = int((player_sprite.getGlobalBounds().left + x) / 64);
    int right = int((player_sprite.getGlobalBounds().left + 32 + x) /64);
    int top = int((player_sprite.getGlobalBounds().top + y)/64);
    int down = int((player_sprite.getGlobalBounds().top + 32 + y)/64);

    if(left == 0 or top == 0 or down == 19 or right == 19) {
        if (left == 0 and sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x = 0;
        }
        if (top == 0 and sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y = 0;
        }
        if (down == 19 and sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y = 0;
        }
        if (right == 19 and sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x = 0;
        }
    }else if(map[left][top] == 0 || map[left][down] == 0 || map[right][top] == 0 || map[right][down] == 0){

    }

    player_sprite.move(x,y);
}


void Player::drawPlayer(sf::RenderWindow& window) {
    window.draw(player_sprite);
}


