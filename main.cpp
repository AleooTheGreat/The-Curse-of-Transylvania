#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <Helper.h>
#include "env_fixes.h"
#include "header/Room.h"


int main() {


    ///window
    sf::RenderWindow window;
    window.create(sf::VideoMode(400,400), "My window", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    ///texture
    Room room = Room();

    while(window.isOpen()) {

        sf::Event event{};
            while(window.pollEvent(event)){



                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();
            window.draw(room.tiles[0][0]->sprite);
            window.draw(room.tiles[0][1]->sprite);
            window.display();
    }
    return 0;
}
