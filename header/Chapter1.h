//
// Created by pasca on 5/27/2024.
//

#ifndef OOP_CHAPTER1_H
#define OOP_CHAPTER1_H
#include<iostream>
#include<array>
#include<fstream>
#include "Map.h"
#include "Player.h"
#include "Bat.h"
#include "ScoreDisplay.h"

///Aici avem tema 1 deci nimic special.Doar le am facut sa fie mai frumos organizate.

class Chapter1{
public:
    explicit Chapter1();
    unsigned short int keepCondition();
    void render(sf::RenderWindow& windows);
    void update(sf::Time deltaTime);
private:

    std::array<std::string,Map_height> map1;
    Player main_player;
    Bat bat1;
    Bat bat2;
    Bat bat3;
    enum situation{
        Defeat,
        Next,
        Playing
    };
    situation stage;
    void readMapFromFile(const std::string& filePath);
    ScoreDisplay<int> scoreDisplay;
};


#endif //OOP_CHAPTER1_H
