#ifndef OOP_CHAPTER2_H
#define OOP_CHAPTER2_H

#include <vector>
#include <array>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
#include "Map.h"
#include "Vampir.h"
#include "NPC.h"
#include "Global.h"
#include "Skelet.h"
#include "Zombie.h"

class Chapter2 {
public:
    explicit Chapter2();
    void generateEnemies();
    int keepPlaying();
    void update();
    void render(sf::RenderWindow& window);
    static void testCopyAndSwap();

private:
    static void populate(int nivel_wave,int count);
    std::array<std::string, Map_height> map2;
    Player main_player;
    NPC help_player;
    static std::vector<std::shared_ptr<Enemy>> enemies;
    static std::vector<Position> poziti;
    enum tip_wave {
        Begin,
        Medium,
        Hard
    };
    tip_wave wave;
    enum tip_Playing {
        Playing,
        Defeat,
        Victory
    };
    tip_Playing stage;
    static std::unordered_map<unsigned long long, bool> frq;
    void readFromFile(const std::string& filePath);
};

#endif //OOP_CHAPTER2_H
