//
// Created by pasca on 3/31/2024.
//

#ifndef OOP_BAT_H
#define OOP_BAT_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bat {
public:

    explicit Bat(unsigned int hp = 20, float dmg = 5.0, const std::string& texturePath = "textures/Bat.png");

    Bat& operator=(const Bat& other);
    Bat(const Bat& other);

    ~Bat();

    void update(float x = 100, float y = 100);
    void draw(sf::RenderWindow& window);

private:

    float bat_power;
    unsigned int bat_hp;
    sf::Sprite bat_sprite;
    sf::Texture bat_texture;
    std::string bat_texturePath;
};


#endif //OOP_BAT_H
