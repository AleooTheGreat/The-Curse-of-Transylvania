//
// Created by pasca on 5/27/2024.
//

#include "../header/Chapter1.h"
#include "../header/GameExceptions.h"

Chapter1::Chapter1() {

    readMapFromFile("maps/map1.txt");

    ///Initializari
    Bat bat4(bat1);  ///Aici demonstram ca functioneaza copy si cu egal si &Bat
    bat3 = bat4;
    bat3.setPosition(768,960);
    bat2 = bat1;

    stage = Playing;
}

void Chapter1::update() {
    if (main_player.getHp() > 0 && (bat1.getHp() > 0 || bat2.getHp() > 0 || bat3.getHp() > 0)) {
        main_player.handleInput();
        main_player.update(Map::convert_map(map1));

        if (bat1.getHp() > 0) {
            bat1.update(main_player, Map::convert_map(map1));
            if (bat1.getHp() <= 0) {
                scoreDisplay.addScore(bat1.getScoreValue());
            }
        }

        if (bat2.getHp() > 0) {
            bat2.update(main_player, Map::convert_map(map1));
            if (bat2.getHp() <= 0) {
                scoreDisplay.addScore(bat2.getScoreValue());
            }
        }

        if (bat3.getHp() > 0) {
            bat3.update(main_player, Map::convert_map(map1));
            if (bat3.getHp() <= 0) {
                scoreDisplay.addScore(bat3.getScoreValue());
            }
        }

        stage = Playing;
    } else if (main_player.getHp() < 0) {
        stage = Defeat;
    } else {
        stage = Next;
    }
}

unsigned short int Chapter1::keepCondition() {
    switch(stage){
        case Defeat: {
            return 0;
        }
        case Next: {
            return 2;
        }
        default: {
            return 1;
        }
    }

}

void Chapter1::render(sf::RenderWindow &window) {
    if(stage == Playing) {

        Map::draw(Map::convert_map(map1), window);
        main_player.drawPlayer(window);

        if(bat1.getHp() > 0) {
            bat1.draw(window);
        }
        if(bat2.getHp() > 0) {
            bat2.draw(window);
        }
        if(bat3.getHp() > 0) {
            bat3.draw(window);
        }
    }

    scoreDisplay.draw(window);
}

void Chapter1::readMapFromFile(const std::string& filePath) {
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        throw FileLoadException("Could not open file: " + filePath);
    }

    std::string line;
    int index = 0;

    while (std::getline(fin, line) && index < Map_height) {
        map1[index] = line;
        index++;
    }

    if (index < Map_height) {
        throw FileLoadException("File is incomplete: " + filePath);
    }

    fin.close();
}
