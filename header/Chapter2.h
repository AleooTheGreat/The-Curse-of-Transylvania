#ifndef CHAPTER2_H
#define CHAPTER2_H

#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>
#include <typeinfo>
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

    [[maybe_unused]]Chapter2(const Chapter2& other);
    Chapter2& operator=(Chapter2 other);


private:

    friend void swap(Chapter2& first, Chapter2& second) noexcept;

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

    std::chrono::time_point<std::chrono::steady_clock> hardLevelStartTime;
    bool hardLevelStartTimeSet = false;

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
    void duplicateZombies();

};

#endif // CHAPTER2_H
