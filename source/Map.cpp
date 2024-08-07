//
// Created by pasca on 3/18/2024.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include "../header/Map.h"
#include "../header/GameExceptions.h"

void Map::draw(const std::array<std::array<Cell, Map_height>,Map_width>& i_map,sf::RenderWindow& window) {
    sf::Sprite cell_sprite;
    sf::Texture wall_texture;
    sf::Texture floor_texture;


    if (!wall_texture.loadFromFile("textures/wall.png")) {
        throw TextureLoadException("Failed to load wall.png");
    }
    if (!floor_texture.loadFromFile("textures/brick_floor.png")) {
        throw TextureLoadException("Failed to load brick_floor.png");
    }


    for (unsigned char a = 0; a < Map_width; a++) {
        for (unsigned char b = 0; b < Map_height; b++) {
            cell_sprite.setPosition(float(Cell_size * a), float(Cell_size * b));
            if (i_map[a][b] == Cell::Wall) {
                cell_sprite.setTexture(wall_texture);
            } else {
                cell_sprite.setTexture(floor_texture);
            }
            window.draw(cell_sprite);
        }
    }
}

std::array<std::array<Cell, Map_height>, Map_width> Map::convert_map(const std::array<std::string,Map_height>& map_sketch) {
    std::array<std::array<Cell, Map_height>, Map_height> output_map{};

    for(unsigned char a = 0; a < Map_height; a++){
        for (unsigned char b = 0 ; b < Map_width; b++){

            switch(map_sketch[a][b]){
                case('#'):
                    output_map[b][a] = Cell::Wall;
                    break;
                default:
                    output_map[b][a] = Cell::Floor;
                    break;
            }
        }
    }



    return output_map;
}


bool Map::map_collision_player(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>, Map_width> i_map) {
    bool collision = false;

    int topLeftX = i_x / Cell_size;
    int topLeftY = i_y / Cell_size;

    int bottomRightX = (i_x + 30) / Cell_size;
    int bottomRightY = (i_y + 55) / Cell_size;


    for (int x = topLeftX; x <= bottomRightX; ++x) {
        for (int y = topLeftY; y <= bottomRightY; ++y) {

            if (x >= 0 && x < Map_width && y >= 0 && y < Map_height) {

                if (i_map[x][y] == Cell::Wall) {
                    collision = true;
                    break;
                }
            }
        }

        if (collision) break;
    }

    return collision;
}

bool Map::map_collision(unsigned short i_x, unsigned short i_y, std::array<std::array<Cell, Map_height>, Map_width> i_map) {

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
        }

        if (0 <= x2 && 0 <= y2 && Map_height > y2 && Map_width > x2) {
            if (Cell::Wall == i_map[x2][y2]) {
                output = true;
            }
        }
    }
    return output;
}

Map::~Map() {
    std::cout<<"Sunt destructorul Map"<<'\n';
}


