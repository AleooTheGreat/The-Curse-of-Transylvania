#include "header/GameEngine.h"
#include "header/GameExceptions.h"
#include <iostream>
#include <SFML/Graphics.hpp>

bool isMouseOverSprite(const sf::Sprite& sprite, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    return spriteBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

int main() {

    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Game Menu");
    bool wasStarted = false;

    sf::Font font;
    if (!font.loadFromFile("font/aerial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Sprite playButtonSprite;
    sf::Texture playButtonTexture;
    if (!playButtonTexture.loadFromFile("textures/play_button.png")) {
        std::cerr << "Error loading play button texture" << std::endl;
        return EXIT_FAILURE;
    }
    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(462, 880);

    sf::Sprite menu;
    sf::Texture menuTexture;

    if (!menuTexture.loadFromFile("textures/menu.png")) {
        std::cerr << "Error loading menu texture" << std::endl;
        return EXIT_FAILURE;
    }
    menu.setTexture(menuTexture);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverSprite(playButtonSprite, window)) {
                    window.close();
                    try {
                        GameEngine* gameEngine = GameEngine::getInstance();
                        wasStarted = true;
                        gameEngine->run();
                    } catch (const GameException& e) {
                        std::cerr << "Game exception caught: " << e.what() << std::endl;
                        return EXIT_FAILURE;
                    } catch (const std::exception& e) {
                        std::cerr << "Standard exception caught: " << e.what() << std::endl;
                        return EXIT_FAILURE;
                    } catch (...) {
                        std::cerr << "Unknown exception caught" << std::endl;
                        return EXIT_FAILURE;
                    }
                }
            }
        }

        if (!wasStarted) {
            window.clear();
            window.draw(menu);
            window.draw(playButtonSprite);
            window.display();
        }
    }

    return EXIT_SUCCESS;
}
