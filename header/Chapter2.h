//
// Created by pasca on 5/27/2024.
//

#ifndef OOP_CHAPTER2_H
#define OOP_CHAPTER2_H
#include <vector>
#include <array>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
#include "Map.h"
#include "Vampir.h"
#include "NPC.h"
#include "Global.h"

class Chapter2 {
public:
    explicit Chapter2();
    void generateEnemies();
    void update();
    void render(sf::RenderWindow& window);
private:
    std::array<std::string,Map_height> map2;
    Player main_player;
    NPC help_player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<Position> poziti;
};


#endif //OOP_CHAPTER2_H
