//
// Created by Alex Pascaru on 23.03.2024.
//

#ifndef OOP_GLOBAL_H
#define OOP_GLOBAL_H

constexpr unsigned char Cell_size = 64;
//constexpr unsigned char Player_size = 32; //I must adjust it later
constexpr unsigned char Map_height = 20;
constexpr unsigned char Map_width = 20;

enum Cell{
    Wall,
    Floor
};

struct Position
{
    float x;
    float y;

    bool operator==(const Position& i_position) const
    {
        return this->x == i_position.x && this->y == i_position.y;
    }
};

#endif //OOP_GLOBAL_H
