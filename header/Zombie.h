//
// Created by pasca on 6/1/2024.
//

#ifndef OOP_ZOMBIE_H
#define OOP_ZOMBIE_H

#include "Enemy.h"
#include <memory>
#include <cmath>
#include <iostream>

class Zombie : public Enemy{
public:
    explicit Zombie(int hp = 50, float dmg = 5, float speed = 0.5, std::string texturePath = "textures/zombie.png");
    void update(Player &p, NPC& npc) override;
    void drawEnemy(sf::RenderWindow& window) override;
    std::shared_ptr<Enemy> clone() const override;
    int getEnemyHp() const override;
    Zombie(const Zombie& other);
    Zombie& operator=(Zombie other);
    void positionUpdate(float x,float y);
private:
    friend void swap(Zombie &first, Zombie &second) noexcept;
    bool player_collision(Player &player) const;
    int z_hp;
    float z_dmg;
    float z_speed;
    sf::Sprite z_sprite;
    sf::Texture z_texture;
    std::string z_texture_path;
    sf::Clock attackTimer;
    sf::Clock getAttacked;
};


#endif //OOP_ZOMBIE_H
