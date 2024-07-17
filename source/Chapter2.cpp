#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../header/Chapter2.h"
#include "../header/GameExceptions.h"
#include "../header/Map.h"
#include "../header/HealthPotion.h"
#include "../header/DamagePotion.h"

std::unordered_map<unsigned long long, bool> Chapter2::frq = {};
std::vector<Position> Chapter2::poziti = {
        {100, 100}, {150, 250}, {350, 250}, {700, 200}, {1000, 300},
        {1000, 1100}, {900, 100}, {1050, 250}, {1250, 1250}, {790, 900},
        {1100, 100}, {100, 1100}, {50, 1050}, {200, 800}, {300, 700},
        {450, 50}, {500, 1000}, {950, 950}, {1100, 1100}, {850, 850},
        {75, 600}, {675, 25}, {725, 75}, {775, 125}, {825, 175},
        {875, 225}, {925, 275}, {975, 325}, {1025, 375}, {1075, 425}
};

Chapter2::Chapter2() : wave(WaveLevel::BEGIN), stage(Playing), hardLevelStartTimeSet(false), scoreDisplay() {
    readFromFile("maps/map2.txt");
    generateEnemies();

    auto& textureManager = TextureManager::getInstance();
    if (!textureManager.loadTexture("health_potion", "textures/health_potion.png")) {
        throw TextureLoadException("Failed to load health potion texture.");
    }
    if (!textureManager.loadTexture("damage_potion", "textures/damage_potion.png")) {
        throw TextureLoadException("Failed to load damage potion texture.");
    }

    healthPotionSprite.setTexture(textureManager.getTexture("health_potion"));
    damagePotionSprite.setTexture(textureManager.getTexture("damage_potion"));

    lastPotionSpawnTime = std::chrono::steady_clock::now();
}

void Chapter2::generateEnemies() {
    switch (wave) {
        case WaveLevel::BEGIN:
            populate(WaveLevel::BEGIN, 4);
            break;
        case WaveLevel::MEDIUM:
            populate(WaveLevel::MEDIUM, 5);
            break;
        case WaveLevel::HARD:
            populate(WaveLevel::BEGIN, 3);
            populate(WaveLevel::MEDIUM, 4);
            populate(WaveLevel::HARD, 2);
            break;
    }
    frq.clear();
}

void Chapter2::update(sf::Time dt) {
    main_player.handleInput();
    main_player.update(Map::convert_map(map2), dt);

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastPotionSpawnTime).count();

    if (elapsedTime > 5) {
        spawnRandomPotion();
        lastPotionSpawnTime = currentTime;
    }

    handlePotions();
    handleEnemies(dt);
    handleHardWave();
    handleStageTransition();
}

void Chapter2::handlePotions() {
    for (auto it = potions.begin(); it != potions.end();) {
        if (main_player.getBounds().intersects(it->getGlobalBounds())) {
            if (it->getTexture() == healthPotionSprite.getTexture()) {
                auto potion = std::make_unique<HealthPotion>();
                main_player.usePotion(std::move(potion));
            } else if (it->getTexture() == damagePotionSprite.getTexture()) {
                auto potion = std::make_unique<DamagePotion>();
                main_player.usePotion(std::move(potion));
            }
            it = potions.erase(it);
        } else {
            ++it;
        }
    }
}

void Chapter2::handleEnemies(sf::Time dt) {
    for (auto it = enemies.begin(); it != enemies.end();) {
        if ((*it)->getEnemyHp() <= 0) {
            updateScore(*it);
            it = enemies.erase(it);
        } else {
            (*it)->update(main_player, help_player, dt);
            ++it;
        }
    }
}

void Chapter2::handleHardWave() {
    if (wave == WaveLevel::HARD && !hardLevelStartTimeSet) {
        hardLevelStartTime = std::chrono::steady_clock::now();
        hardLevelStartTimeSet = true;
    } else if (wave == WaveLevel::HARD) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - hardLevelStartTime).count();

        if (elapsedTime > 3) {
            duplicateZombies();
            hardLevelStartTimeSet = false;
        }
    }
}

void Chapter2::handleStageTransition() {
    auto currentTime = std::chrono::steady_clock::now();

    if (allEnemiesDefeated()) {
        if (!stageTransitioning) {
            stageTransitioning = true;
            stageTransitionTime = std::chrono::steady_clock::now();
        } else {
            auto transitionElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - stageTransitionTime).count();
            if (transitionElapsedTime >= 3) {
                switch (wave) {
                    case WaveLevel::BEGIN:
                        main_player.buff(120, main_player.get_attack() + 3);
                        help_player.heal(200);
                        wave = WaveLevel::MEDIUM;
                        break;
                    case WaveLevel::MEDIUM:
                        main_player.buff(140, main_player.get_attack() + 5);
                        help_player.heal(350);
                        wave = WaveLevel::HARD;
                        hardLevelStartTimeSet = false;
                        break;
                    case WaveLevel::HARD:
                        stage = Victory;
                        break;
                }
                enemies.clear();
                generateEnemies();
                std::cout << main_player.getHp() << " " << main_player.get_attack() << '\n';
                std::cout << help_player.getHp() << "\n";
                stageTransitioning = false;
            }
        }
    }

    if (main_player.getHp() < 0 || help_player.getHp() < 0) {
        stage = Defeat;
    }
}

void Chapter2::spawnRandomPotion() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 1);
    std::uniform_int_distribution<int> posDistrib(100, 900);

    int potionType = distrib(gen);
    int x, y;

    do {
        x = posDistrib(gen);
        y = posDistrib(gen);
    } while (std::sqrt(std::pow(x - 600, 2) + std::pow(y - 600, 2)) < 100);

    sf::Sprite potionSprite = (potionType == 0) ? healthPotionSprite : damagePotionSprite;
    potionSprite.setPosition((float)x, (float)y);
    potions.push_back(potionSprite);
}

void Chapter2::updateScore(const std::shared_ptr<Enemy>& enemy) {
    scoreDisplay.addScore(enemy->getScoreValue());
}

void Chapter2::duplicateZombies() {
    int currentZombieCount = 0;

    for (const auto& enemy : enemies) {
        if (dynamic_cast<Zombie*>(enemy.get())) {
            currentZombieCount++;
            if (currentZombieCount >= 20) {
                break;
            }
        }
    }

    if (currentZombieCount < 20) {
        populate(WaveLevel::HARD, 2);
    }
}

bool Chapter2::allEnemiesDefeated() {
    for (const auto& enemy : enemies) {
        if (enemy->getEnemyHp() > 0) {
            return false;
        }
    }
    return true;
}

void Chapter2::render(sf::RenderWindow &window) {
    Map::draw(Map::convert_map(map2), window);
    help_player.drawNPC(window);
    for (auto& it : enemies) {
        if (it->getEnemyHp() > 0) {
            it->drawEnemy(window);
        }
    }
    for (auto& potion : potions) {
        window.draw(potion);
    }
    main_player.drawPlayer(window);
    scoreDisplay.draw(window);
}

int Chapter2::keepPlaying() {
    switch (stage) {
        case Victory: return 1;
        case Defeat: return 0;
        default: return 2;
    }
}

void Chapter2::readFromFile(const std::string &filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        throw FileLoadException("Could not open file: " + filePath);
    }

    int index = 0;
    std::string line;
    while (std::getline(fin, line) && index < Map_height) {
        map2[index] = line;
        index++;
    }

    if (index < Map_height) {
        throw FileLoadException("File is incomplete: " + filePath);
    }

    fin.close();
}

[[maybe_unused]]Chapter2::Chapter2(const Chapter2& other)
        : main_player(other.main_player), help_player(other.help_player), map2(other.map2),
          enemies(other.enemies), wave(other.wave),
          stage(other.stage), hardLevelStartTimeSet(other.hardLevelStartTimeSet),
          hardLevelStartTime(other.hardLevelStartTime) {}

Chapter2& Chapter2::operator=(Chapter2 other) {
    swap(*this, other);
    return *this;
}

void swap(Chapter2& first, Chapter2& second) noexcept {
    using std::swap;
    swap(first.wave, second.wave);
    swap(first.stage, second.stage);
    swap(first.enemies, second.enemies);
    swap(first.main_player, second.main_player);
    swap(first.help_player, second.help_player);
    swap(first.map2, second.map2);
    swap(first.hardLevelStartTime, second.hardLevelStartTime);
    swap(first.hardLevelStartTimeSet, second.hardLevelStartTimeSet);
}

void Chapter2::populate(WaveLevel level, int count) {
    for (int i = 0; i < count; ++i) {
        auto enemy = EnemyFactory::createEnemy(level);
        Position pos = getRandomPosition();
        enemy->positionUpdate(pos.x, pos.y);
        enemies.emplace_back(enemy->clone());
    }
}

Position Chapter2::getRandomPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

    unsigned long long number = distrib(gen);
    while (frq[number]) {
        number = distrib(gen);
    }
    frq[number] = true;
    return poziti[number];
}
