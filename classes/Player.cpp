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
    velocity.x = 0.f;
    velocity.y = 0.f;
}

Player::Player(const Player& other):m_name{other.m_name},m_hp{other.m_hp},m_speed{other.m_speed},m_power{other.m_power}{
    std::cout << "Player fost apelat" << '\n';
}

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

    velocity.x = 0;
    velocity.y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += m_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= m_speed;
    }

}

void Player::update(sf::Time deltaTime, std::vector<std::vector<int>> &map) {

    int left = int((player_sprite.getGlobalBounds().left + velocity.x * deltaTime.asSeconds()) / 64);
    int right = left + 1;
    int top = int((player_sprite.getGlobalBounds().top + velocity.y * deltaTime.asSeconds())  / 64);
    int down = top + 1;

    if (map[left][top] == 0 || map[right][down] == 0 || map[right][top] == 0 || map[left][down] == 0){
        velocity.x = 0;
        velocity.y = 0;
    }else {
        player_sprite.move(velocity * deltaTime.asSeconds());
    }
}


void Player::drawPlayer(sf::RenderWindow& window) {
    window.draw(player_sprite);
}


