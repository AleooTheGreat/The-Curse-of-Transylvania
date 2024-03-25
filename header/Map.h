//
// Created by pasca on 3/18/2024.
//

#ifndef OOP_MAP_H
#define OOP_MAP_H


#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "Global.h"

class Map {
public:
    Map();
    static void draw(const std::array<std::array<Cell, Map_height>,Map_width>& map,sf::RenderWindow &window);
    std::vector<std::vector<int>>& getMap();
    static std::array<std::array<Cell, Map_height>,Map_width> convert_map(const std::vector<std::vector<int>>& map1);

private:
    std::vector<std::vector<int>> map1;
    sf::RenderTexture mapTexture;
};


#endif //OOP_MAP_H
