//
// Created by pasca on 5/27/2024.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include<SFML/Graphics/RenderWindow.hpp>
#include<memory>
#include<vector>
#include "Player.h"
#include "NPC.h"
#include "Global.h"

class Enemy {
public:
    virtual void update(Player& p, NPC& npc) = 0;
    virtual void drawEnemy(sf::RenderWindow& window) = 0;
    virtual std::shared_ptr<Enemy> clone() const = 0;
    virtual ~Enemy() = default;
    Enemy() = default;
protected:
    Enemy(const Enemy &other) = default;
    Enemy &operator=(const Enemy &other) = default;
};


#endif //OOP_ENEMY_H
