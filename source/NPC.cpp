//
// Created by pasca on 5/27/2024.
//

#include "../header/NPC.h"

NPC::NPC(short int hp, std::string texture) : npc_hp{hp},npc_string{std::move(texture)}{
    npc_texture.loadFromFile(npc_string);
    npc_sprite.setTexture(npc_texture);
    npc_sprite.setPosition(600,600);
}

void NPC::update() {

}

void NPC::drawNPC(sf::RenderWindow& window) {
    window.draw(npc_sprite);
}

Position NPC::getPosition() {
    return {npc_sprite.getPosition().x,npc_sprite.getPosition().y};
}

void NPC::loseHp(float dmg) {
    npc_hp -= (short)(dmg);
}

int NPC::getHp() const {
    return npc_hp;
}

void NPC::heal(short hp) {
    npc_hp = hp;
}



