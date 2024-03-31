//
// Created by pasca on 3/31/2024.
//

#include<iostream>
#include<string>
#include "../header/Bat.h"

Bat::Bat(unsigned int hp, float dmg, const std::string& texturePath): bat_power(dmg), bat_hp(hp), bat_texturePath(texturePath) {
    bat_texture.loadFromFile(texturePath);
    bat_sprite.setTexture(bat_texture);
    bat_sprite.setPosition(100,100);
}

Bat::Bat(const Bat& other): bat_power(other.bat_power), bat_hp(other.bat_hp), bat_texturePath(other.bat_texturePath) {

    bat_texture.loadFromFile(bat_texturePath);
    bat_sprite.setTexture(bat_texture);
    bat_sprite.setPosition(other.bat_sprite.getPosition());

    std::cout << "Bat has been copied successfully.\n";
}

Bat& Bat::operator=(const Bat& other) {

    if (this != &other) {

        bat_hp = other.bat_hp;
        bat_power = other.bat_power;
        bat_texturePath = other.bat_texturePath;


        bat_texture.loadFromFile(bat_texturePath);
        bat_sprite.setTexture(bat_texture);
        bat_sprite.setPosition(other.bat_sprite.getPosition());

        std::cout << "Bat has been copied successfully.\n";
    }
    return *this;
}

void Bat::update(float x, float y){
    bat_sprite.setPosition(x,y);
}

Bat::~Bat() {
    std::cout << "Bat has been destroyed successfully.\n";
}

void Bat::draw(sf::RenderWindow& window) {
    window.draw(bat_sprite);
}