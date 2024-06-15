//
// Created by pasca on 6/15/2024.
//

#ifndef OOP_POTION_H
#define OOP_POTION_H

#include "Player.h"

class Player;

class Potion {
public:
    virtual ~Potion() = default;
    virtual void use(Player& player) = 0;
};

#endif //OOP_POTION_H
