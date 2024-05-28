//
// Created by pasca on 5/27/2024.
//

#include <random>
#include <chrono>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "../header/Chapter2.h"

Chapter2::Chapter2() : poziti({
        {100, 100}, {150, 250}, {350, 250}, {700, 200}, {1000, 300},
        {1000, 1100}, {900, 100}, {1050, 250}, {1250, 1250}, {790, 900},
        {1100, 100}, {100, 1100}}),wave{Begin}, stage{Playing} {

    readFromFile("maps/map2.txt");
    generateEnemies();

}

void Chapter2::generateEnemies() {

    std::unordered_map<unsigned long long,bool> frq;

    if(wave == Begin) {
        ///generam 4 vampiri
        for (int i = 0; i <= 3; i++) {

            auto vamp1 = std::make_shared<Vampir>();

            ///generam random
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

            unsigned long long number = distrib(gen);
            while (frq[number]) {
                number = distrib(gen);
            }
            frq[number] = true;
            vamp1->positionUpdate(poziti[number].x, poziti[number].y);

            enemies.emplace_back(vamp1);
        }

        frq.clear();
    }else if(wave == Medium){
        ///generam 5 skeleti
        for (int i = 0; i <= 4; i++) {

            auto skelet = std::make_shared<Skelet>();

            ///generam random
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

            unsigned long long number = distrib(gen);
            while (frq[number]) {
                number = distrib(gen);
            }
            frq[number] = true;
            skelet->positionUpdate(poziti[number].x, poziti[number].y);

            enemies.emplace_back(skelet);
        }

        frq.clear();
    }else if(wave == Hard){
        for (int i = 0; i <= 4; i++) {

            auto skelet = std::make_shared<Skelet>();

            ///generam random
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

            unsigned long long number = distrib(gen);
            while (frq[number]) {
                number = distrib(gen);
            }
            frq[number] = true;
            skelet->positionUpdate(poziti[number].x, poziti[number].y);

            enemies.emplace_back(skelet);
        }
        for (int i = 0; i <= 3; i++) {

            auto vamp1 = std::make_shared<Vampir>();

            ///generam random
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<unsigned long long> distrib(0, poziti.size() - 1);

            unsigned long long number = distrib(gen);
            while (frq[number]) {
                number = distrib(gen);
            }
            frq[number] = true;
            vamp1->positionUpdate(poziti[number].x, poziti[number].y);

            enemies.emplace_back(vamp1);
        }

        frq.clear();
    }
}

void Chapter2::update() {
    main_player.handleInput();
    main_player.update(Map::convert_map(map2));
    unsigned long long cnt = 0;
    for(auto& it:enemies){
        if(it->getEnemyHp() > 0) {
            it->update(main_player, help_player);
        }else{
            cnt++;
        }
    }

    if(cnt == enemies.size() && wave == Begin){
        cnt = 0;
        main_player.buff(120,6);
        help_player.heal(150);
        wave = Medium;
        enemies.clear();
        generateEnemies();
        std::cout<<main_player.getHp() << " " << main_player.get_attack() << '\n';
        std::cout<<help_player.getHp() << "\n";
    }else if(cnt == enemies.size() && wave == Medium){
        cnt = 0;
        main_player.buff(140,9);
        help_player.heal(170);
        wave = Hard;
        enemies.clear();
        generateEnemies();
        std::cout<<main_player.getHp() << " " << main_player.get_attack() << '\n';
        std::cout<<help_player.getHp() << "\n";
    }

    if(main_player.getHp() < 0 || help_player.getHp() < 0){
        stage = Defeat;
    }else if(wave == Hard && cnt == enemies.size()){
        stage = Victory;
    }
}

void Chapter2::render(sf::RenderWindow &window) {
    Map::draw(Map::convert_map(map2),window);
    main_player.drawPlayer(window);
    help_player.drawNPC(window);
    for(auto& it:enemies){
        if(it->getEnemyHp() > 0) {
            it->drawEnemy(window);
        }
    }
}

int Chapter2::keepPlaying() {
    switch(stage) {
        case Victory:{
            return 1;
        }
        case Defeat:{
            return 0;
        }
        default:{
            return 2;
        }
    }
}

void Chapter2::readFromFile(const std::string &filePath) {
    std::ifstream fin(filePath);

    int index = 0;
    std::string line;

    while(std::getline(fin,line) && index < Map_height){
        map2[index] = line;
        index ++;
    }

    fin.close();
}


