//
// Created by pasca on 5/27/2024.
//

#ifndef OOP_NPC_H
#define OOP_NPC_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
class NPC : public Player{
public:
    explicit NPC(short int hp = 100, std::string texture = "textures/help_girl.png");
    void update();
    void drawNPC(sf::RenderWindow& window);
    void loseHp(float dmg) override;
    int getHp() const override;
    void heal(short int hp);
    Position getPosition() override;
private:
    short int npc_hp;
    sf::Texture npc_texture;
    sf::Sprite npc_sprite;
    std::string npc_string;
};


#endif //OOP_NPC_H
