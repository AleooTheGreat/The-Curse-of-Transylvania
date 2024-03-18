//
// Created by pasca on 3/10/2024.
//

#include "../header/Player.h"
#include <string>
#include <iostream>
#include <utility>
#include <SFML/Window/Keyboard.hpp>

Player::Player(std::string name, unsigned int hp, float speed, float power): m_name(std::move(name)), m_hp(hp), m_speed(speed), m_power(power) {
    //player_sprite.setScale(0.25f, 0.25f);
    player_texture.loadFromFile("textures/Player.png");
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(640.0f, 640.0f);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player_sprite.move(-m_speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player_sprite.move(+m_speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player_sprite.move(0, +m_speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player_sprite.move(0, -m_speed);
    }
}
void Player::update(sf::Time deltaTime) {

}

void Player::draw(sf::RenderWindow& window) {
    window.draw(player_sprite);
}


