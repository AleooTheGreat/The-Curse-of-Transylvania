//
// Created by pasca on 6/15/2024.
//

#ifndef OOP_DAMAGEPOTION_H
#define OOP_DAMAGEPOTION_H
#include "Potion.h"
#include "Player.h"

class DamagePotion : public Potion {
public:
    void use(Player& player) override {
        player.buff(player.getHp(), player.get_attack() + 1);
    }
};

#endif //OOP_DAMAGEPOTION_H
