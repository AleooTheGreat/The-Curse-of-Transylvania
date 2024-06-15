#include "header/GameEngine.h"
#include "header/GameExceptions.h"
#include <iostream>
#include <SFML/Graphics.hpp>

bool isMouseOverButton(const sf::RectangleShape& button, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
}

int main() {

    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Game Menu");
    bool wasStarted = false;

    sf::Font font;
    if (!font.loadFromFile("font/aerial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return EXIT_FAILURE;
    }

    sf::RectangleShape playButton(sf::Vector2f(200, 100));
    playButton.setPosition(412, 800);
    playButton.setFillColor(sf::Color::Blue);

    sf::Sprite menu;
    sf::Texture menu_texture;

    menu_texture.loadFromFile("textures/menu.png");
    menu.setTexture(menu_texture);

    sf::Text playText;
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(
            playButton.getPosition().x + (playButton.getSize().x - playText.getLocalBounds().width) / 2,
            playButton.getPosition().y + (playButton.getSize().y - playText.getLocalBounds().height) / 2 - 10
    );

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (isMouseOverButton(playButton, window)) {
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

        if(!wasStarted) {
            window.clear();
            window.draw(menu);
            window.draw(playButton);
            window.draw(playText);
            window.display();
        }
    }

    return EXIT_SUCCESS;
}
