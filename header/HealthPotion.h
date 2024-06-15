//
// Created by pasca on 6/15/2024.
//

#ifndef OOP_HEALTHPOTION_H
#define OOP_HEALTHPOTION_H

#include "Player.h"
#include "Potion.h"

class HealthPotion : public Potion {
public:
    void use(Player& player) override {
        player.buff(player.getHp() + 20, player.get_attack());
    }
};
#endif //OOP_HEALTHPOTION_H
