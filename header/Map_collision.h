//
// Created by pasca on 3/31/2024.
//

#ifndef OOP_MAP_COLLISION_H
#define OOP_MAP_COLLISION_H


class Map_collision {
public:
    static bool map_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>,Map_width> i_map);
};


#endif //OOP_MAP_COLLISION_H
