//
// Created by pasca on 5/27/2024.
//

#include <utility>
#include <valarray>
#include <iostream>

#include "../header/Vampir.h"

Vampir::Vampir(unsigned short int hp, unsigned short int dmg, float speed, std::string  texturePath) : v_hp{hp}, v_dmg{dmg},
v_speed{speed}, vampir_texturePath{std::move(texturePath)}, target{100,100}, chase{true} {
    vampir_texture.loadFromFile(vampir_texturePath);
    vampir_sprite.setTexture(vampir_texture);
    vampir_sprite.setPosition(600,600);
}

void Vampir::update(Player& p, NPC& npc) {


    if(chase){
        target = npc.getPosition();
    }else{

    }


    if(player_collision( p)){
        std::cout<<"Ne-am lovit"<<'\n';
    }
    if(player_collision(npc)){
        std::cout<<"NPC ul a fost lovit"<<'\n';
        chase = false;
    }

    //target = npc.getPosition();

    Position currentPosition = {vampir_sprite.getPosition().x, vampir_sprite.getPosition().y};
    Position direction = {target.x - currentPosition.x,target.y-currentPosition.y};
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    // Simulate movement towards the target
    vampir_sprite.move(direction.x * v_speed,direction.y * v_speed);


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



