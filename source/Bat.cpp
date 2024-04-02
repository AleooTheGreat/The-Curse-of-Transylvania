//
// Created by pasca on 3/31/2024.
//

#include <cmath>
#include<iostream>
#include<string>
#include <SFML/Window/Keyboard.hpp>
#include "../header/Bat.h"
#include "../header/Map.h"

Bat::Bat(int hp, float speed, float dmg, std::string texturePath)
    : bat_power(dmg),bat_speed(speed), bat_hp(hp), bat_texturePath(std::move(texturePath)),
    position{64,64}, direction(0), target{600,600} {
    bat_texture.loadFromFile(bat_texturePath);
    bat_sprite.setTexture(bat_texture);

}

/*Bat::Bat(const Bat& other): bat_power(other.bat_power), bat_speed(other.bat_speed), bat_hp(other.bat_hp),
                            bat_texturePath(other.bat_texturePath),position{64,64}, direction(0),target{0,0} {

    bat_texture.loadFromFile(bat_texturePath);
    bat_sprite.setTexture(bat_texture);
    std::cout << "Bat has been copied successfully.\n";
}

Bat& Bat::operator=(const Bat& other) {

    if (this != &other) {

        bat_hp = other.bat_hp;
        bat_power = other.bat_power;
        bat_speed = other.bat_speed;
        bat_texturePath = other.bat_texturePath;
        position = {64,64};
        direction = 0;
        target = {0,0};


        bat_texture.loadFromFile(bat_texturePath);
        bat_sprite.setTexture(bat_texture);
        bat_sprite.setPosition(other.bat_sprite.getPosition());

        std::cout << "Bat has been copied successfully.\n";
    }
    return *this;
}*/


std::ostream& operator<<(std::ostream& os, const Bat& bat) {
    os <<"Bat current hp: " << bat.bat_hp << '\n';
    return os;
}

float Bat::get_target_distance(unsigned char i_direction) const
{
    float x = position.x;
    float y = position.y;

    switch (i_direction)
    {
        case 0:
        {
            x += bat_speed;

            break;
        }
        case 1:
        {
            y -= bat_speed;

            break;
        }
        case 2:
        {
            x -= bat_speed;

            break;
        }
        case 3:
        {
            y += bat_speed;
        }
        default:
        {

        }
    }

    return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));
}

bool Bat::player_collision(Player& player) const
{

    sf::FloatRect batBounds = bat_sprite.getGlobalBounds();
    sf::FloatRect playerBounds = player.getBounds();

    return batBounds.intersects(playerBounds);
}

void Bat::update(Player& player, std::array<std::array<Cell, Map_height>, Map_width> i_map) {

    float speed = 1.f;
    unsigned char available_ways = 0;

    std::array<bool, 4> walls{};
    walls[0] = Map::map_collision((unsigned short)(speed + position.x), (unsigned short)(position.y), i_map);
    walls[1] = Map::map_collision((unsigned short)(position.x), (unsigned short)(position.y - speed), i_map);
    walls[2] = Map::map_collision((unsigned short)(position.x - speed), (unsigned short)(position.y), i_map);
    walls[3] = Map::map_collision((unsigned short)(position.x), (unsigned short)(speed + position.y), i_map);

    unsigned char optimal_direction = 4;
    target = player.getPosition();
   // std::cout<<target.x<<" "<< target.y<<'\n';

    for (unsigned char a = 0; a < 4; a++)
    {
        if (a == (2 + direction) % 4)
        {
            continue;
        }
        else if (0 == walls[a])
        {
            if (4 == optimal_direction)
            {
                optimal_direction = a;
            }

            available_ways++;

            if (get_target_distance(a) < get_target_distance(optimal_direction))
            {
                optimal_direction = a;
            }
        }
    }

    if (1 < available_ways)
    {
        direction = optimal_direction;
    }
    else
    {
        if (4 == optimal_direction)
        {
            direction = (2 + direction) % 4;
        }
        else
        {
            direction = optimal_direction;
        }
    }

    switch (direction)
    {
        case 0:
        {
            position.x += speed;

            break;
        }
        case 1:
        {
            position.y -= speed;

            break;
        }
        case 2:
        {
            position.x -= speed;

            break;
        }
        case 3:
        {
            position.y += speed;
        }
    }

    if(player_collision(player)) {
        if(attackTimer.getElapsedTime().asSeconds() >= 0.75) {
            player.loseHp(bat_power);
            std::cout << "Player HP: " << player.getHp() << '\n';
            attackTimer.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            std::cout << bat_hp << '\n';
            if(getAttacked.getElapsedTime().asSeconds() < 0.007) {
                std::cout<<"hit"<<'\n';
                bat_hp -= (int) (std::floor(player.get_attack()));
            }if(getAttacked.getElapsedTime().asSeconds() > 0.3){
                std::cout<<"reset"<<'\n';
                getAttacked.restart();
            }
        }

    }



}

Bat::~Bat() {
    std::cout << "Bat has been destroyed successfully.\n";
}

void Bat::draw(sf::RenderWindow& window) {
    bat_sprite.setPosition(position.x,position.y);
    window.draw(bat_sprite);
}

void Bat::reset() {
    bat_hp = 20;
    position ={64,64};
}

int Bat::getHp() const{
    return bat_hp;
}

