#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Helper.h>
#include "env_fixes.h"
#include "header/Room.h"
#include "header/Player.h"


int main() {

    Player player;

    sf::Clock clock;

    ///window
    sf::RenderWindow window(sf::VideoMode(1 * 1280 + 64, 1 * 1280 + 64), "IDK", sf::Style::Default);
    window.setView(sf::View(sf::FloatRect(0, 0, 1280, 1280)));

    sf::Sprite grid_sprite;
    sf::Texture grid_texture;
    sf::Sprite wall_sprite;
    sf::Texture wall_texture;

    grid_texture.loadFromFile("textures/Brick_floor.png");
    grid_sprite.setTexture(grid_texture);
    wall_texture.loadFromFile("textures/Wall.png");
    wall_sprite.setTexture(wall_texture);

    window.setVerticalSyncEnabled(true);

    while(window.isOpen()) {

        sf::Event event{};
            while(window.pollEvent(event)){



                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            ///HandleInput
        player.handleInput();

            ///Time delta etc
        sf::Time deltaTime = clock.restart();
        player.update(deltaTime);

        window.clear();

        ///Budget Map
        for(int i = 0 ; i <= int(1280/64); i++){
            for(int j = 0; j <= int(1280/64);j++){

                if(i == 0 || j == 0 || j == (int(1280/64) - 1) || i == (int(1280/64) - 1)) {
                    wall_sprite.setPosition(float(i*64),float(j*64));
                    window.draw(wall_sprite);
                }else{
                    grid_sprite.setPosition(float(i*64),float(j*64));
                    window.draw(grid_sprite);
                }
            }
        }

        ///Player
        player.draw(window);

        window.display();
    }
    return 0;
}
