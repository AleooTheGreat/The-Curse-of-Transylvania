//
// Created by pasca on 3/11/2024.
//

#include <iostream>
#include "../header/Blood_Bat.h"

Blood_Bat::Blood_Bat(const std::string &name, unsigned int hp, float speed, float damage) : Enemy(name,hp,speed), bat_damage(damage) {
    std::cout<<"Blood_Bat a fost creeat" << '\n';
}

Blood_Bat::Blood_Bat(const Enemy &other1, const Blood_Bat &other) : Enemy(other1), bat_damage{other.bat_damage} {
    std::cout<<"S-a facut o copia a lui Bat"<<'\n';
}

Blood_Bat:: ~Blood_Bat() {
    std::cout << "U got destructed"<< '\n';
}