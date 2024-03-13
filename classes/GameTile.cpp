//
// Created by pasca on 3/13/2024.
//

#include "../header/GameTile.h"


GameTile::GameTile(const std::string& textureName, float x, float y , bool passable , bool exit){
    if(!setUpSprite(textureName)){
        return;
    }
     pos = sf::Vector2f(x,y);
     sprite.setPosition(pos);
     isFree = passable;
     isExit = exit;
}

bool GameTile::setUpSprite(const std::string& textureName) {
    if(!texture.loadFromFile("textures/Brick_floor.png")){
        return false;
    }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,64,64));
    return true;
}

