#ifndef CHAPTER2_H
#define CHAPTER2_H

#include <unordered_map>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Player.h"
#include "NPC.h"
#include "Map.h"

class Chapter2 {
public:
    Chapter2();

    void update();
    void render(sf::RenderWindow &window);
    int keepPlaying();

    static void testCopyAndSwap();

private:

    enum GameState{
        Playing,
        Defeat,
        Victory
    };

    enum WaveLevel {
        BEGIN = 1,
        MEDIUM = 2,
        HARD = 3
    };

    WaveLevel wave;
    GameState stage;

    std::vector<std::shared_ptr<Enemy>> enemies;


    Player main_player;
    NPC help_player;

    std::array<std::string, Map_height> map2;

    static std::unordered_map<unsigned long long, bool> frq;
    static std::vector<Position> poziti;

    static std::shared_ptr<Enemy> createEnemy(WaveLevel level);

    void readFromFile(const std::string &filePath);
    void generateEnemies();
    void populate(WaveLevel level, int count);
    static Position getRandomPosition();
    bool allEnemiesDefeated();

};

#endif // CHAPTER2_H
