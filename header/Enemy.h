#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>
#include "Player.h"
#include "NPC.h"
#include "Global.h"

class Enemy {
public:
    Enemy() = default;
    Enemy(int hp, unsigned short int dmg, float speed) : e_hp(hp), e_dmg(dmg), e_speed(speed) {}

    virtual void update(Player& p, NPC& npc, sf::Time deltaTime) = 0;
    virtual void drawEnemy(sf::RenderWindow& window) = 0;
    virtual int getEnemyHp() const = 0;
    virtual void positionUpdate(float x, float y) = 0;
    virtual std::shared_ptr<Enemy> clone() const = 0;
    virtual double getScoreValue() const = 0;

    virtual ~Enemy() = default;

protected:
    Enemy(const Enemy &other) = default;
    Enemy &operator=(const Enemy &other) = default;

    int e_hp;
    unsigned short int e_dmg;
    float e_speed;

    friend void swap(Enemy& first, Enemy& second) noexcept {
        using std::swap;
        swap(first.e_hp, second.e_hp);
        swap(first.e_dmg, second.e_dmg);
        swap(first.e_speed, second.e_speed);
    }
};

#endif // OOP_ENEMY_H
