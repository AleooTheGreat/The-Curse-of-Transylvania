#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip>
#include <sstream>

template <typename T>
class ScoreDisplay {
private:
    T score;
    sf::Font font;
    sf::Text text;

public:
    ScoreDisplay() : score(0) {
        if (!font.loadFromFile("font/aerial.ttf")) {
            throw std::runtime_error("Failed to load font");
        }

        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Green);
        text.setPosition(10, 10);
    }

    void setScore(T newScore) {
        score = newScore;
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(1) << score;
        text.setString("Score: " + stream.str());
    }

    T getScore() const {
        return score;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(text);
    }
};
