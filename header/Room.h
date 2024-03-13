//
// Created by pasca on 3/10/2024.
//
#pragma once
#ifndef OOP_ROOM_H
#define OOP_ROOM_H
#include <SFML/Graphics.hpp>
#include<vector>
#include "gameTile.h"

class Room {

public:
    std::vector<std::vector<GameTile*>> tiles;
    int gridLength;
    Room();
private:
    sf::Vector2i exitPos;
    sf::Vector2i playerPos;
    std::vector<sf::Vector2i> enemyPos;
    void setUpInitialState();
    void setUpEnemyPositions();
    void setUpTiles();
};


#endif //OOP_ROOM_H
