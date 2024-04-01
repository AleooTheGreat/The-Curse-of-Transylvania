#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <array>
#include "header/Player.h"
#include "header/Map.h"
#include "header/Bat.h"


int main() {

    Bat bat1;
    /*Bat bat2 = bat1;
    bat2.update(200,300);
    Bat bat3(bat1);
    bat3.update(300,400);*/
    Player player;
    Map map;

    sf::Texture end_screen_texture;
    sf::Sprite end_screen;
    end_screen_texture.loadFromFile("textures/end_screen.png");
    end_screen.setTexture(end_screen_texture);
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

            if(player.getHp() > 0 && bat1.getHp() > 0) {
                ///HandleInput
                player.handleInput();
                player.update(Map::convert_map(map.getMap()));
                bat1.update(player, Map::convert_map(map.getMap()));

                window.clear();

                Map::draw(Map::convert_map(map.getMap()), window);
                player.drawPlayer(window);
                bat1.draw(window);
                //bat2.draw(window);
                //bat3.draw(window);
            }else{
                window.clear();
                window.draw(end_screen);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                    player.reset();
                    bat1.reset();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                    return 0;
                }
            }
        window.display();
    }
    return 0;
}
