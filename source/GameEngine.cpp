//
// Created by pasca on 4/2/2024.
//

#include "../header/GameEngine.h"
#include <iostream>

GameEngine::GameEngine(): window(sf::VideoMode(1 * 1280 + 64, 1 * 1280 + 64), "My Window", sf::Style::Default){

    ///Initializari
    Bat bat4(bat1);  ///Aici demonstram ca functioneaza copy si cu egal si &Bat
    bat3 = bat4;
    bat3.setPosition(768,960);
    bat2 = bat1;
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

    if(main_player_first.getHp() > 0 && (bat1.getHp() > 0 || bat2.getHp() > 0 || bat3.getHp() > 0)) {
        main_player_first.handleInput();
        main_player_first.update(Map::convert_map(map.getMap()));
        if(bat1.getHp() > 0) {
            bat1.update(main_player_first, Map::convert_map(map.getMap()));
        }
        if(bat2.getHp() > 0) {
            bat2.update(main_player_first, Map::convert_map(map.getMap()));
        }
        if(bat3.getHp() > 0) {
            bat3.update(main_player_first, Map::convert_map(map.getMap()));
        }
    }else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            main_player_first.reset();
            bat1.reset(1);
            bat2.reset(2);
            bat3.reset(3);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }
    }

}

void GameEngine::render() {
    window.clear();

    if(main_player_first.getHp() > 0 && (bat1.getHp() > 0 || bat2.getHp() > 0 || bat3.getHp() > 0)) {

        Map::draw(Map::convert_map(map.getMap()), window);
        main_player_first.drawPlayer(window);

        if(bat1.getHp() > 0) {
            bat1.draw(window);
        }
        if(bat2.getHp() > 0) {
            bat2.draw(window);
        }
        if(bat3.getHp() > 0) {
            bat3.draw(window);
        }
    } else {
        if(main_player_first.getHp() <= 0) {
            window.draw(end_screen);
            std::cout<<"Ai murit! ;)"<<'\n';
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

GameEngine::~GameEngine() {
    std::cout<<"Sunt destructorul GameEngine!"<<'\n';
}
