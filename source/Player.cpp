//
// Created by pasca on 3/10/2024.
//

#include "../header/Player.h"
#include "../header/Map_collision.h"
#include <cmath>
#include <iostream>
#include <array>
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <utility>

Player::Player(std::string  name, int hp, float speed, float power, std::string texture)
                :m_name(std::move(name)), m_hp(hp), m_speed(speed), m_power(power), m_texture(std::move(texture)) {
    player_texture.loadFromFile(m_texture);
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(640.0f, 640.0f);
    direction = 0;
    position = {0,0};
}

/*Player::Player(const Player& other):m_name{other.m_name},m_hp{other.m_hp},m_speed{other.m_speed},m_power{other.m_power},m_texture(other.m_texture){

    player_texture.loadFromFile(m_texture);
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(other.player_sprite.getPosition());

    std::cout << "Player fost apelat" << '\n';
    x = 0;
    y = 0;
}///O sa o folosesc dar nu trec cu verde si ma enerveaza

Player&Player::operator=(const Player&other) {
    m_name = other.m_name;
    m_hp = other.m_hp;
    m_speed = other.m_speed;
    m_power = other.m_power;
    m_texture = other.m_texture;

    player_texture.loadFromFile(m_texture);
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(other.player_sprite.getPosition());

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

    position.x = 0;
    position.y = 0;

    attack_texture.loadFromFile("textures/attack.png");

}


void Player::update(const std::array<std::array<Cell, Map_height>,Map_width>& map) {

    std::array<bool, 4> walls{};
    walls[0] = Map_collision::map_collision((unsigned short)(m_speed + player_sprite.getPosition().x), (unsigned short)player_sprite.getPosition().y, map);
    walls[1] = Map_collision::map_collision((unsigned short)(player_sprite.getPosition().x), (unsigned short)(player_sprite.getPosition().y - m_speed), map);
    walls[2] = Map_collision::map_collision((unsigned short)(player_sprite.getPosition().x - m_speed), (unsigned short)(player_sprite.getPosition().y), map);
    walls[3] = Map_collision::map_collision((unsigned short)(player_sprite.getPosition().x), (unsigned short)(m_speed + player_sprite.getPosition().y), map);

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (0 == walls[0])
        {
            direction = 0;
            position.x += m_speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (0 == walls[1])
        {
            direction = 1;
            position.y -= m_speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (0 == walls[2])
        {
            direction = 2;
            position.x -= m_speed;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (0 == walls[3])
        {
            direction = 3;
            position.y += m_speed;
        }
    }



}


void Player::drawPlayer(sf::RenderWindow& window) {
    player_sprite.move(position.x,position.y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        player_sprite.setTexture(attack_texture);
    }else{
        player_sprite.setTexture(player_texture);//
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
    return {player_sprite.getPosition().x,player_sprite.getPosition().x};
}

sf::FloatRect Player::getBounds(){
    return player_sprite.getGlobalBounds();
}

void Player::reset(){
    m_hp = 100;
    player_sprite.setPosition(640,640);
}


