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
    explicit Zombie(int hp = 160, unsigned short int dmg = 4, float speed = 105, std::string texturePath = "textures/zombie.png");

    void update(Player &p, NPC& npc, sf::Time deltaTime) override;
    void drawEnemy(sf::RenderWindow& window) override;

    int getEnemyHp() const override;
    void positionUpdate(float x,float y) override;

    double getScoreValue() const override;

    std::shared_ptr<Enemy> clone() const override;

    Zombie(const Zombie& other);
    Zombie& operator=(Zombie other);

private:
    friend void swap(Zombie &first, Zombie &second) noexcept;
    bool player_collision(Player &player) const;
    sf::Sprite z_sprite;
    sf::Texture z_texture;
    std::string z_texture_path;
    sf::Clock attackTimer;
    sf::Clock getAttacked;
};


#endif //OOP_ZOMBIE_H
