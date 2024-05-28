//
// Created by pasca on 5/27/2024.
//

#include <utility>
#include <valarray>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "../header/Vampir.h"

Vampir::Vampir(int hp, unsigned short int dmg, float speed, std::string  texturePath) : v_hp{hp}, v_dmg{dmg},
v_speed{speed}, vampir_texturePath{std::move(texturePath)}, target{100,100}, chase{true}, initialPosition({0,0}) {
    vampir_texture.loadFromFile(vampir_texturePath);
    vampir_sprite.setTexture(vampir_texture);
    vampir_sprite.setPosition(600,600);
    circularRotation = false;
    rotationAngle = 0.0f;
    rotationRadius = 150.0f;
    rotationSpeed = 0.01f;
    verticalOffset = 0.0f;
}

void Vampir::update(Player& p, NPC& npc) {
    if (circularRotation) {

        rotationAngle += rotationSpeed;
        verticalOffset += std::sin(rotationAngle) * 0.5f; // Adjust the vertical movement as needed
        float x = initialPosition.x + rotationRadius * std::cos(rotationAngle);
        float y = initialPosition.y + rotationRadius * std::sin(rotationAngle) + verticalOffset;
        vampir_sprite.setPosition(x, y);
    } else {
        if (chase) {
            target = npc.getPosition();
        }
        if (player_collision(npc)) {
            std::cout << "NPC ul a fost lovit" << '\n';
            chase = false;
            circularRotation = true;
            initialPosition.x = vampir_sprite.getPosition().x;
            initialPosition.y = vampir_sprite.getPosition().y;
        }

        Position currentPosition = {vampir_sprite.getPosition().x, vampir_sprite.getPosition().y};
        Position direction = {target.x - currentPosition.x, target.y - currentPosition.y};
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction.x /= length;
            direction.y /= length;
        }

        vampir_sprite.move(direction.x * v_speed, direction.y * v_speed);
    }

    if (player_collision(npc)) {
        if (attackTimer.getElapsedTime().asMilliseconds() >= 750) {
            npc.loseHp(v_dmg);
            std::cout << "NPC HP: " << npc.getHp() << '\n';
            attackTimer.restart();
        }
    }
    if (player_collision(p)) {
        if(attackTimer.getElapsedTime().asMilliseconds() >= 1050) {
            p.loseHp(v_dmg);
            std::cout << "Player HP: " << p.getHp() << '\n';
            attackTimer.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){

            if(getAttacked.getElapsedTime().asMilliseconds() < 20) {
                std::cout<<"hit"<<'\n';
                v_hp -= (int) (std::floor(p.get_attack()));
                std::cout << v_hp << '\n';
            }if(getAttacked.getElapsedTime().asMilliseconds() > 200){
                getAttacked.restart();
            }
        }
    }
}

bool Vampir::player_collision(Player& p) const {
    sf::FloatRect vampirBounds = vampir_sprite.getGlobalBounds();
    sf::FloatRect playerBounds = p.getBounds();
    return vampirBounds.intersects(playerBounds);
}

void Vampir::drawEnemy(sf::RenderWindow &window) {
    window.draw(vampir_sprite);
}


void Vampir::positionUpdate(float x,float y) {
    vampir_sprite.setPosition(x,y);
}

std::shared_ptr<Enemy> Vampir::clone() const {
    return std::make_shared<Vampir>(*this);
}

int Vampir::getEnemyHp() const {
    return v_hp;
}



