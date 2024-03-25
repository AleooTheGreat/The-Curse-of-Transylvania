//
// Created by pasca on 3/18/2024.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "../header/Map.h"

Map::Map(int width,int height): m_width {width}, m_height{height} {

    this->map1 = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };
}


void Map::draw(const std::array<std::array<Cell, Map_height>,Map_width>& i_map,sf::RenderWindow& window){
    sf::Sprite cell_sprite;
    sf::Texture wall_texture;
    sf::Texture floor_texture;

    wall_texture.loadFromFile("textures/Wall.png");
    floor_texture.loadFromFile("textures/Brick_floor.png");

    for(unsigned char a = 0; a < Map_width; a++){
        for(unsigned char b = 0 ; b < Map_height; b++){
            cell_sprite.setPosition(float(Cell_size * a), float(Cell_size * b));
            if(i_map[a][b] == Cell::Wall) {
                cell_sprite.setTexture(wall_texture);
            }else{
                cell_sprite.setTexture(floor_texture);
            }
            window.draw(cell_sprite);
        }
    }
}

std::vector<std::vector<int>>& Map::getMap(){
    return map1;
}

std::array<std::array<Cell, Map_height>, Map_width> Map::convert_map(const std::vector<std::vector<int>>& map_sketch) {
    std::array<std::array<Cell, Map_height>, Map_height> output_map{};

    for(unsigned char a = 0; a < Map_height; a++){
        for (unsigned char b = 0 ; b < Map_width; b++){
            if(map_sketch[a][b] == 1){
                output_map[a][b] = Cell::Floor;
            }else{
                output_map[a][b] = Cell::Wall;
            }
        }
    }

    return output_map;
}

