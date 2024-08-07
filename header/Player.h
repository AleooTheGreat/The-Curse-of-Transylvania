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
#include <memory>
#include "Global.h"
#include "Potion.h"

class Player{
public:
    ///Constructor
    explicit Player(std::string  name = "Gigel", int hp = 100, float speed = 175.f, float power = 4.0f,
                    std::string texture = "textures/player.png");

    ///Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    void usePotion(std::unique_ptr<Potion> potion);
    void handleInput();
    void update(const std::array<std::array<Cell, Map_height>,Map_width>& map, sf::Time deltaTime);
    void drawPlayer(sf::RenderWindow& window);
    virtual void loseHp(float dmg);
    float get_attack() const;
    virtual int getHp() const;
    void buff(int hp, float power);
    virtual Position getPosition();
    sf::FloatRect getBounds();

    ///Destroy(Mosh Pit)
    ~Player();

private:
    std::string m_name;
    int m_hp;
    float m_speed;
    float m_power;
    std::string m_texture;
    sf::Sprite player_sprite;
    sf::Texture player_texture;
    Position position{};
    unsigned char direction;
    sf::Texture attack_texture;
    sf::Texture player_texture_left;
    sf::Texture attack_texture_left;
};


#endif //OOP_PLAYER_H