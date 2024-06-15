#ifndef CHAPTER2_H
#define CHAPTER2_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <unordered_map>
#include <chrono>
#include "Player.h"
#include "NPC.h"
#include "Enemy.h"
#include "Potion.h"
#include "ScoreDisplay.h"
#include "TextureManager.h"
#include "EnemyFactory.h"

class Chapter2 {
public:
    Chapter2();
    void update();
    void render(sf::RenderWindow& window);
    int keepPlaying();


    [[maybe_unused]]Chapter2(const Chapter2& other);
    Chapter2& operator=(Chapter2 other);


private:
    void generateEnemies();
    void handlePotions();
    void handleEnemies();
    void handleHardWave();
    void handleStageTransition();
    void spawnRandomPotion();
    void updateScore(const std::shared_ptr<Enemy>& enemy);
    void duplicateZombies();
    bool allEnemiesDefeated();
    void readFromFile(const std::string& filePath);
    static Position getRandomPosition();
    void populate(WaveLevel level, int count);

    static std::unordered_map<unsigned long long, bool> frq;
    static std::vector<Position> poziti;

    Player main_player;
    NPC help_player;
    std::array<std::basic_string<char>, 20> map2;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<sf::Sprite> potions;
    WaveLevel wave;
    enum Stage { Playing, Victory, Defeat } stage;
    bool hardLevelStartTimeSet;
    bool stageTransitioning = false;
    std::chrono::steady_clock::time_point hardLevelStartTime;
    std::chrono::steady_clock::time_point lastPotionSpawnTime;
    std::chrono::steady_clock::time_point stageTransitionTime;
    ScoreDisplay<double> scoreDisplay;

    sf::Sprite healthPotionSprite;
    sf::Sprite damagePotionSprite;

    friend void swap(Chapter2& first, Chapter2& second) noexcept;
};

#endif // CHAPTER2_H
