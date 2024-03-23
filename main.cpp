#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "header/Player.h"
#include "header/Map.h"


int main() {

    Player player;
    Map map(1280,1280);
    sf::Sprite testin;
    sf::Texture testin_texture;
    sf::Clock clock;

    testin_texture.loadFromFile("textures/Wall.png");
    testin.setTexture(testin_texture);
    testin.setPosition(0.f,0.f);

    ///window
    sf::RenderWindow window(sf::VideoMode(1 * 1280 + 64, 1 * 1280 + 64), "IDK", sf::Style::Default);
    window.setView(sf::View(sf::FloatRect(0, 0, 1280, 1280)));

    window.setVerticalSyncEnabled(true);

    while(window.isOpen()) {

        sf::Event event{};
            while(window.pollEvent(event)){



                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            ///HandleInput
      //  player.handleInput();
       // player.update(map.getMap());

        window.clear();

        Map::draw(Map::convert_map(map.getMap()), window);
       // player.drawPlayer(window);
        window.display();
    }
    return 0;
}
