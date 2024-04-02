//
// Created by pasca on 4/2/2024.
//

#include "../header/GameEngine.h"
#include <iomanip>

GameEngine::GameEngine(): window(sf::VideoMode(1 * 1280 + 64, 1 * 1280 + 64), "IDK", sf::Style::Default){

    is_render = false;
    ///Initializam window-ul
    window.setView(sf::View(sf::FloatRect(0, 0, 1280, 1280)));
    window.setVerticalSyncEnabled(true);

    ///Alte resurse care apartin tot de window
    win_screen_texture.loadFromFile("textures/win_screen.png");
    end_screen_texture.loadFromFile("textures/end_screen.png");
    end_screen.setTexture(end_screen_texture);
    win_screen.setTexture(win_screen_texture);
}

void GameEngine::run() {
    while(window.isOpen()){
    processEvents();
    update();
    render();
    }
}

void GameEngine::processEvents() {
    sf::Event event{};
    while(window.pollEvent(event)){

        if(event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameEngine::update() {
    if(player.getHp() > 0 && bat1.getHp() > 0) {
        player.handleInput();
        player.update(Map::convert_map(map.getMap()));
        bat1.update(player, Map::convert_map(map.getMap()));
    }else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            player.reset();
            bat1.reset();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }
    }

}

void GameEngine::render() {
    window.clear();

    if(player.getHp() > 0 && bat1.getHp() > 0) {
        Map::draw(Map::convert_map(map.getMap()), window);
        player.drawPlayer(window);
        bat1.draw(window);
    } else {
        if(player.getHp() <= 0) {
            window.draw(end_screen);
        }else{
            window.draw(win_screen);
        }
    }

    window.display();
}

std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine) {
    os << std::boolalpha <<gameEngine.is_render;
    return os;
}
