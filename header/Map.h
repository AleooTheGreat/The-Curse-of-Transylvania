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
    static bool map_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>,Map_width> i_map);
    static bool map_collision_player(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>,Map_width> i_map);
    static void draw(const std::array<std::array<Cell, Map_height>,Map_width>& map, sf::RenderWindow &window);
    std::array<std::string,Map_height>& getMap();
    static std::array<std::array<Cell, Map_height>,Map_width> convert_map(const std::array<std::string,Map_height>& map1);

    ///<<
    friend std::ostream& operator<<(std::ostream& os, const Map& map);
    ~Map();
private:
    std::array<std::string,Map_height> map1;
    bool was_draw;
};


#endif //OOP_MAP_H
