//
// Created by pasca on 5/27/2024.
//

#ifndef OOP_VAMPIR_H
#define OOP_VAMPIR_H
#include "Enemy.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include<string>

class Vampir : public Enemy{
public:
    explicit Vampir(unsigned short int hp = 100, unsigned short int dmg = 10, float speed = 1.4, std::string  texturePath = "textures/vampir.png");
    void update(Player& p, NPC& npc) override;
    void drawEnemy(sf::RenderWindow& window) override;
    void positionUpdate(float x, float y);
    bool player_collision(Player& main_player) const;
    std::shared_ptr<Enemy> clone() const override;
private:
    unsigned short int v_hp;
    unsigned short int v_dmg;
    float v_speed;
    sf::Sprite vampir_sprite;
    sf::Texture vampir_texture;
    std::string vampir_texturePath;
    Position target;
    bool chase;
};


#endif //OOP_VAMPIR_H
