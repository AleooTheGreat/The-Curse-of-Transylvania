#include "../header/Vampir.h"
#include "../header/GameExceptions.h"
#include <utility>
#include <valarray>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>


Vampir::Vampir(int hp, unsigned short int dmg, float speed, std::string texturePath)
        : Enemy(hp,dmg,speed), chase{true},vampir_texturePath{std::move(texturePath)},
          target{100, 100}, initialPosition({0, 0}), circularRotation{false},
          rotationAngle{0.0f}, rotationRadius{150.0f}, rotationSpeed{0.01f}, verticalOffset{0.0f} {

    if (!vampir_texture.loadFromFile(vampir_texturePath)) {
        throw TextureLoadException("Failed to load Vampir texture: " + vampir_texturePath);
    }

    vampir_sprite.setTexture(vampir_texture);
    vampir_sprite.setPosition(600, 600);
}

Vampir::Vampir(const Vampir& other)
        : Enemy(other.e_hp,other.e_dmg,other.e_speed), chase{other.chase},
          vampir_texturePath{other.vampir_texturePath}, target{other.target},
          initialPosition{other.initialPosition}, circularRotation{other.circularRotation},
          rotationAngle{other.rotationAngle}, rotationRadius{other.rotationRadius},
          rotationSpeed{other.rotationSpeed}, verticalOffset{other.verticalOffset} {
    try {
        if (!vampir_texture.loadFromFile(vampir_texturePath)) {
            throw TextureLoadException("Failed to load Vampir texture: " + vampir_texturePath);
        }
    } catch (const TextureLoadException& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    vampir_sprite.setTexture(vampir_texture);
    vampir_sprite.setPosition(other.vampir_sprite.getPosition());
}

Vampir& Vampir::operator=(Vampir other) {
    swap(*this, other);
    return *this;
}

void swap(Vampir& first, Vampir& second) noexcept {
    using std::swap;
    swap(static_cast<Enemy&>(first),static_cast<Enemy&>(second));
    swap(first.chase, second.chase);
    swap(first.vampir_texturePath, second.vampir_texturePath);
    swap(first.vampir_sprite, second.vampir_sprite);
    swap(first.vampir_texture, second.vampir_texture);
    swap(first.target, second.target);
    swap(first.initialPosition, second.initialPosition);
    swap(first.circularRotation, second.circularRotation);
    swap(first.rotationAngle, second.rotationAngle);
    swap(first.rotationRadius, second.rotationRadius);
    swap(first.rotationSpeed, second.rotationSpeed);
    swap(first.verticalOffset, second.verticalOffset);
    swap(first.attackTimer, second.attackTimer);
    swap(first.getAttacked, second.getAttacked);
}

void Vampir::update(Player& p, NPC& npc) {
    if (circularRotation) {
        rotationAngle += rotationSpeed;
        verticalOffset += std::sin(rotationAngle) * 0.5f;
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

        vampir_sprite.move(direction.x * e_speed, direction.y * e_speed);
    }

    if (player_collision(npc)) {
        if (attackTimer.getElapsedTime().asMilliseconds() >= 750) {
            npc.loseHp(e_dmg);
            std::cout << "NPC HP: " << npc.getHp() << '\n';
            attackTimer.restart();
        }
    }
    if (player_collision(p)) {
        if(attackTimer.getElapsedTime().asMilliseconds() >= 1050) {
            p.loseHp(e_dmg);
            std::cout << "Player HP: " << p.getHp() << '\n';
            attackTimer.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if(getAttacked.getElapsedTime().asMilliseconds() < 20) {
                std::cout << "hit" << '\n';
                e_hp -= static_cast<int>(std::floor(p.get_attack()));
                std::cout << e_hp << '\n';
            }
            if(getAttacked.getElapsedTime().asMilliseconds() > 200){
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
    return e_hp;
}

double Vampir::getScoreValue() const {
    return 2.5;
}
