//
// Created by pasca on 3/10/2024.
//

#include "../header/Player.h"
#include "../header/Map.h"
#include "../header/GameExceptions.h"
#include <cmath>
#include <iostream>
#include <array>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <utility>

Player::Player(std::string  name, int hp, float speed, float power, std::string texture)
        :m_name(std::move(name)), m_hp(hp), m_speed(speed), m_power(power), m_texture(std::move(texture)) {

    if (!player_texture.loadFromFile(m_texture)) {
        throw TextureLoadException("Failed to load player texture: " + m_texture);
    }

    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(640.0f, 576.0f);
    direction = 0;
    position = {0, 0};
}
std::ostream& operator<<(std::ostream& os, const Player& main_player) {
    os << "Player Name: " << main_player.m_name << ", HP: " << main_player.m_hp <<'\n';
    return os;
}

Player:: ~Player() {
    std::cout << "Sunt destructorul Player"<< '\n';
}

void Player::handleInput() {

    position.x = 0;
    position.y = 0;

    attack_texture.loadFromFile("textures/attack.png");
    attack_texture_left.loadFromFile("textures/attack_left.png");
    player_texture_left .loadFromFile("textures/player_left.png");

}


void Player::update(const std::array<std::array<Cell, Map_height>,Map_width>& map, sf::Time dt) {


    float speed = m_speed * dt.asSeconds();
    std::array<bool, 4> walls{};
    walls[0] = Map::map_collision_player((unsigned short)(speed + player_sprite.getPosition().x), (unsigned short)player_sprite.getPosition().y, map);
    walls[1] = Map::map_collision_player((unsigned short)(player_sprite.getPosition().x), (unsigned short)(player_sprite.getPosition().y - speed), map);
    walls[2] = Map::map_collision_player((unsigned short)(player_sprite.getPosition().x - speed), (unsigned short)(player_sprite.getPosition().y), map);
    walls[3] = Map::map_collision_player((unsigned short)(player_sprite.getPosition().x), (unsigned short)(speed + player_sprite.getPosition().y), map);

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (0 == walls[0])
        {
            direction = 0;
            position.x += speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (0 == walls[1])
        {
            direction = 1;
            position.y -= speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (0 == walls[2])
        {
            direction = 2;
            position.x -= speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (0 == walls[3])
        {
            direction = 3;
            position.y += speed;
        }
    }



}


void Player::drawPlayer(sf::RenderWindow& window) {
    player_sprite.move(position.x,position.y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) ){
        if(direction == 0) {
            player_sprite.setTexture(attack_texture);
        }else{
            player_sprite.setTexture(attack_texture_left);
        }
    }else{
        if(direction == 0) {
            player_sprite.setTexture(player_texture);
        }else{
            player_sprite.setTexture(player_texture_left);
        }

    }

    window.draw(player_sprite);
}

float Player::get_attack() const {
    return m_power;
}

void Player::loseHp(float dmg){
    m_hp -= std::ceil(dmg);
}

int Player::getHp() const{
    return m_hp;
}

Position Player::getPosition() {
    return {player_sprite.getPosition().x,player_sprite.getPosition().y};
}

sf::FloatRect Player::getBounds(){
    return player_sprite.getGlobalBounds();
}


void Player::buff(int hp, float power) {
    m_hp = hp;
    m_power = power;
}

void Player::usePotion(std::unique_ptr<Potion> potion) {
    potion->use(*this);
}


