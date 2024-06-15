#include "../header/EnemyFactory.h"
#include "../header/GameExceptions.h"

std::shared_ptr<Enemy> EnemyFactory::createEnemy(WaveLevel level) {
    switch (level) {
        case WaveLevel::BEGIN: return std::make_shared<Vampir>();
        case WaveLevel::MEDIUM: return std::make_shared<Skelet>();
        case WaveLevel::HARD: return std::make_shared<Zombie>();
        default: throw InvalidEnemyTypeException("Invalid enemy type encountered.");
    }
}
