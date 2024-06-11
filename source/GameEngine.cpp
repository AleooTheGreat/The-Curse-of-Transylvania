#include "../header/GameEngine.h"
#include "../header/GameExceptions.h"
#include <iostream>

GameEngine* GameEngine::instance = nullptr;

GameEngine* GameEngine::getInstance() {
    if (instance == nullptr) {
        instance = new GameEngine();
    }
    return instance;
}

GameEngine::GameEngine() : window(sf::VideoMode(1 * 1280 + 64, 1 * 1280 + 64), "My Window", sf::Style::Default) {
    try {
        if (!win_screen_texture.loadFromFile("textures/win_screen.png")) {
            throw TextureLoadException("Failed to load win_screen.png");
        }
        if (!end_screen_texture.loadFromFile("textures/end_screen.png")) {
            throw TextureLoadException("Failed to load end_screen.png");
        }
    } catch (const TextureLoadException& e) {
        std::cerr << e.what() << std::endl;
        window.close();
        throw;
    }

    is_render = false;
    window.setView(sf::View(sf::FloatRect(0, 0, 1280, 1280)));
    window.setVerticalSyncEnabled(true);

    end_screen.setTexture(end_screen_texture);
    win_screen.setTexture(win_screen_texture);

    // Testam copy si swap
    Chapter2::testCopyAndSwap();
}

void GameEngine::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameEngine::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void GameEngine::update() {
    if (ch1.keepCondition() == 1) {
        ch1.update();
    } else if (ch1.keepCondition() == 2) {
        if (ch2.keepPlaying() == 2) {
            ch2.update();
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
    }
}

void GameEngine::render() {
    window.clear();

    if (ch1.keepCondition() == 1) {
        ch1.render(window);
    } else if (ch1.keepCondition() == 2) {
        if (ch2.keepPlaying() == 2) {
            ch2.render(window);
        } else if (ch2.keepPlaying() == 1) {
            window.draw(win_screen);
        } else {
            window.draw(end_screen);
        }
    } else {
        window.draw(end_screen);
    }

    window.display();
}

std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine) {
    os << std::boolalpha << gameEngine.is_render;
    return os;
}

GameEngine::~GameEngine() {
    std::cout << "Sunt destructorul GameEngine!" << '\n';
}
