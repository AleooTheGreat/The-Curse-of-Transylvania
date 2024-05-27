//
// Created by pasca on 4/2/2024.
//

#include "../header/GameEngine.h"
#include <iostream>

GameEngine::GameEngine(): window(sf::VideoMode(1 * 1280 + 64, 1 * 1280 + 64), "My Window", sf::Style::Default){

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
    if(ch1.keepCondition() == 1) {
        ch1.update();
    }else{
        ch2.update();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
           window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }
    }

}

void GameEngine::render() {
    window.clear();

    if(ch1.keepCondition() == 1) {
        ch1.render(window);
    } else {
        if(ch1.keepCondition() == 0) {
            window.draw(end_screen);
            std::cout<<"Ai murit! ;)"<<'\n';
        }else{
            ch2.render(window);
            //window.draw(win_screen);
        }
    }

    window.display();
}

std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine) {
    os << std::boolalpha <<gameEngine.is_render;
    return os;
}

GameEngine::~GameEngine() {
    std::cout<<"Sunt destructorul GameEngine!"<<'\n';
}
