//
// Created by pasca on 3/18/2024.
//

#ifndef OOP_MAP_H
#define OOP_MAP_H


#include <string>
#include <SFML/Graphics/Sprite.hpp>

class Map {
public:
    Map(int width, int height);
    void draw(sf::RenderWindow& window);
    std::vector<std::vector<int>>& getMap();

private:
    int m_width, m_height;
    std::vector<std::vector<int>> map1;
    sf::RenderTexture mapTexture;
};


#endif //OOP_MAP_H
