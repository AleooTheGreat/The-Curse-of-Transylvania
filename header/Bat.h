//
// Created by pasca on 3/31/2024.
//

#ifndef OOP_BAT_H
#define OOP_BAT_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"

class Bat {
public:

    explicit Bat(int hp = 20,float speed = 1, float dmg = 5, std::string texturePath = "textures/bat.png");

    Bat& operator=(const Bat& other);
    Bat(const Bat& other);
    friend std::ostream& operator<<(std::ostream& os,const Bat& bat);

    ~Bat();

    float get_target_distance(unsigned char i_direction) const;
    bool player_collision(Player& player) const;
    void update(Player& player, std::array<std::array<Cell, Map_height>, Map_width> i_map);
    void draw(sf::RenderWindow& window);
    int getHp() const;
    void setPosition(float x, float y);
    int getScoreValue() const;

private:
    float bat_power;
    float bat_speed;
    int bat_hp;
    sf::Sprite bat_sprite;
    sf::Texture bat_texture;
    std::string bat_texturePath;
    Position position;
    unsigned char direction;
    Position target{};
    sf::Clock attackTimer;
    sf::Clock getAttacked;
};


#endif //OOP_BAT_H
