#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <memory>
#include "Enemy.h"
#include "Vampir.h"
#include "Skelet.h"
#include "Zombie.h"

enum class WaveLevel {
    BEGIN,
    MEDIUM,
    HARD
};

class EnemyFactory {
public:
    static std::shared_ptr<Enemy> createEnemy(WaveLevel level);
};

#endif // ENEMYFACTORY_H
