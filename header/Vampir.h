#ifndef OOP_VAMPIR_H
#define OOP_VAMPIR_H

#include "Enemy.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <memory>

class Vampir : public Enemy {
public:

    explicit Vampir(int hp = 60, unsigned short int dmg = 5, float speed = 160, std::string texturePath = "textures/vampir.png");

    Vampir(const Vampir& other);
    Vampir& operator=(Vampir other);

    void update(Player& p, NPC& npc, sf::Time deltaTime) override;
    void drawEnemy(sf::RenderWindow& window) override;

    void positionUpdate(float x, float y) override;
    int getEnemyHp() const override;

    double getScoreValue() const override;

    std::shared_ptr<Enemy> clone() const override;

private:
    friend void swap(Vampir& first, Vampir& second) noexcept;
    bool chase;
    sf::Sprite vampir_sprite;
    sf::Texture vampir_texture;
    std::string vampir_texturePath;
    Position target;
    sf::Clock attackTimer;
    sf::Clock getAttacked;
    bool player_collision(Player& main_player) const;
    Position initialPosition;
    bool circularRotation;
    float rotationAngle;
    float rotationRadius;
    float rotationSpeed;
    float verticalOffset;
};

#endif //OOP_VAMPIR_H
