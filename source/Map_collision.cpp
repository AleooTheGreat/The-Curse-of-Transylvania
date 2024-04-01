//
// Created by pasca on 3/31/2024.
//

#include <array>
#include <cmath>
#include <iostream>
#include "../header/Global.h"
#include "../header/Map_collision.h"
bool Map_collision::map_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>, Map_width> i_map) {

    bool output = false;

    float cell_x = float(i_x) / static_cast<float>(Cell_size);
    float cell_y = float(i_y) / static_cast<float>(Cell_size);

    for (unsigned char a = 0; a < 4; a++) {
        short x2 = 0;
        short y2 = 0;

        switch (a) {
            case 0: //Top left cell
            {
                x2 = static_cast<short>(std::floor(cell_x));
                y2 = static_cast<short>(std::floor(cell_y));

                break;
            }
            case 1: //Top right cell
            {
                x2 = static_cast<short>(std::ceil(cell_x));
                y2 = static_cast<short>(std::floor(cell_y));

                break;
            }
            case 2: //Bottom left cell
            {
                x2 = static_cast<short>(std::floor(cell_x));
                y2 = static_cast<short>(std::ceil(cell_y));

                break;
            }
            case 3: //Bottom right cell
            {
                x2 = static_cast<short>(std::ceil(cell_x));
                y2 = static_cast<short>(std::ceil(cell_y));

                break;
            }
            default:
                std::cout << "Niciun perete" <<'\n';
                //Ma obliga tidy sa am si un default
        }

        //Check we are inside
        if (0 <= x2 && 0 <= y2 && Map_height > y2 && Map_width > x2) {
            if (Cell::Wall == i_map[x2][y2]) {
                output = true;
            }
        }
    }
    return output;
}
