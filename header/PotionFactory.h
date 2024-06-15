//
// Created by pasca on 6/15/2024.
//

#ifndef OOP_POTIONFACTORY_H
#define OOP_POTIONFACTORY_H

#include <memory>
#include "Potion.h"
#include "HealthPotion.h"
#include "DamagePotion.h"

enum class PotionType {
    DAMAGE,
    HEALTH
};

class PotionFactory {
public:
    static std::unique_ptr<Potion> createPotion(PotionType type) {
        switch(type) {
            case PotionType::DAMAGE:
                return std::make_unique<DamagePotion>();
            case PotionType::HEALTH:
                return std::make_unique<HealthPotion>();
            default:
                return nullptr;
        }
    }
};

#endif //OOP_POTIONFACTORY_H
