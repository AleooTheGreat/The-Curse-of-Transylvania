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

sf::Sprite Player::getPlayer() {
    return player_sprite;
}


std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player Name: " << player.m_name << ", HP: " << player.m_hp <<'\n';
    return os;
}

Player:: ~Player() {
    std::cout << "U got destructed"<< '\n';
}

void Player::stopWall(){
    player_sprite.setPosition(400,400);
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

void Player::update(sf::Time deltaTime) {

    sf::FloatRect predictedBox = player_sprite.getGlobalBounds();
    predictedBox.left += velocity.x * deltaTime.asSeconds();
    predictedBox.top += velocity.y * deltaTime.asSeconds();

    bool collisionX = false;
    bool collisionY = false;
    for (int i = 0; i <= int(1280/64); i++) {
        for (int j = 0; j <= int(1280/64); j++) {
            if (i == 0 || j == 0 || j == (int(1280/64) - 1) || i == (int(1280/64) - 1)) {
                sf::FloatRect wallBox(float(i*64), float(j*64), 64.0f, 64.0f);
                if (predictedBox.intersects(wallBox)) {
                    if (predictedBox.intersects(sf::FloatRect(wallBox.left, player_sprite.getGlobalBounds().top, wallBox.width, wallBox.height))) {
                        collisionX = true;
                    }
                    if (predictedBox.intersects(sf::FloatRect(player_sprite.getGlobalBounds().left, wallBox.top, player_sprite.getGlobalBounds().width, wallBox.height))) {
                        collisionY = true;
                    }
                }
            }
        }
    }

    if (!collisionX) {
        player_sprite.move(velocity.x * deltaTime.asSeconds(), 0.f);
    }
    if (!collisionY) {
        player_sprite.move(0.f, velocity.y * deltaTime.asSeconds());
    }

    velocity.x = 0.f;
    velocity.y = 0.f;
}


void Player::draw(sf::RenderWindow& window) {
    window.draw(player_sprite);
}


