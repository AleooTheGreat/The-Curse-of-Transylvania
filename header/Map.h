//
// Created by pasca on 3/18/2024.
//

#ifndef OOP_MAP_H
#define OOP_MAP_H


#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Global.h"

class Map {
public:
    explicit Map() = default;
    static bool map_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>,Map_width> i_map);
    static bool map_collision_player(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>,Map_width> i_map);
    static void draw(const std::array<std::array<Cell, Map_height>,Map_width>& map, sf::RenderWindow &window);
    static std::array<std::array<Cell, Map_height>,Map_width> convert_map(const std::array<std::string,Map_height>& map1);

    ///<<
    ~Map();
};


#endif //OOP_MAP_H
