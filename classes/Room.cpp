//
// Created by pasca on 3/10/2024.
//

#include "../header/Room.h"


Room::Room(){
    gridLength = 5;
    setUpInitialState();

}

void Room::setUpInitialState() {
    exitPos = sf::Vector2i(1,0);
    playerPos = sf::Vector2i (gridLength-1,gridLength-1);
    setUpEnemyPositions();
    setUpTiles();

}

void Room::setUpEnemyPositions() {
    enemyPos.clear();
    enemyPos.emplace_back(0,2);
}

void Room::setUpTiles() {
    tiles.clear();
    std::vector<GameTile*> firstRow;
    firstRow.push_back(new GameTile("textures/Brick_floor.png",0,0,true,false));
    firstRow.push_back(new GameTile("textures/Brick_floor.png",64,0,true,false));
    tiles.push_back(firstRow);
}