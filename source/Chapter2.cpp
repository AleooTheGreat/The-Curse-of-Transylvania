//
// Created by pasca on 5/27/2024.
//

#include <random>
#include <chrono>
#include <unordered_map>
#include "../header/Chapter2.h"

Chapter2::Chapter2() {
    map2 = {
            "####################",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "#                  #",
            "####################"
    };
    ///toate pozitiile posibile de spawn are unui inamic
    poziti = {
            {100, 100}, {150, 250}, {350, 250}, {700, 200}, {1000, 300},
            {1000, 1100}, {900, 100}, {1050, 250}, {1250, 1250}, {790, 900},
            {1100, 100}, {100, 1100}
    };
    generateEnemies();

}

void Chapter2::generateEnemies() {

    std::unordered_map<unsigned long long,bool> frq;

    for(int i = 0 ; i <= 3; i ++){

        auto vamp1 = std::make_shared<Vampir>();

        ///generam random
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

        unsigned long long number = distrib(gen);
        while(frq[number]){
            number = distrib(gen);
        }
        frq[number] = true;
        vamp1->positionUpdate(poziti[number].x,poziti[number].y);

        enemies.emplace_back(vamp1);
    }
}

void Chapter2::update() {
    main_player.handleInput();
    main_player.update(Map::convert_map(map2));
    for(auto& it:enemies){
        it->update(main_player,help_player);
    }
}

void Chapter2::render(sf::RenderWindow &window) {
    Map::draw(Map::convert_map(map2),window);
    main_player.drawPlayer(window);
    help_player.drawNPC(window);
    for(auto& it:enemies) {
        it->drawEnemy(window);
    }
}
