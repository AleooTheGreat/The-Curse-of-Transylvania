//
// Created by pasca on 5/27/2024.
//

#ifndef OOP_SKELET_H
#define OOP_SKELET_H
#include "Enemy.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class Skelet : public Enemy{
public:
    explicit Skelet(int hp = 70, unsigned short int dmg = 3, float speed = 1.7, std::string  texturePath = "textures/skelet.png");
    void update(Player& p, NPC& npc) override;
    void drawEnemy(sf::RenderWindow& window) override;
    void positionUpdate(float x, float y);
    int getEnemyHp() const override;
    std::shared_ptr<Enemy> clone() const override;
private:
    int s_hp;
    unsigned short int s_dmg;
    float s_speed;
    sf::Sprite skelet_sprite;
    sf::Texture skelet_texture;
    std::string skelet_texturePath;
    Position target;
    sf::Clock attackTimer;
    sf::Clock getAttacked;
    bool player_collision(Player& main_player) const;
    Position npcInitialPosition;
    enum SkeletState {
        CHASING_NPC,
        ATTACKING_PLAYER,
        RETURNING_TO_NPC
    };
    SkeletState state;
};


#endif //OOP_SKELET_H
