//
// Created by pasca on 3/11/2024.
//

#include <iostream>
#include <utility>
#include "../header/Enemy.h"

Enemy::Enemy(std::string name, unsigned int hp, float speed): e_name{std::move(name)}, e_hp(hp), e_speed(speed) {
    std::cout<<"S a creeat un enemy"<<'\n';
}

Enemy::Enemy(const Enemy &other) : e_name{other.e_name}, e_hp{other.e_hp}, e_speed{other.e_speed}{
    std::cout<<"S a copiat un enemy"<<'\n';
}

Enemy&Enemy::operator=(const Enemy& other){
    e_name = other.e_name;
    e_hp = other.e_hp;
    e_speed = other.e_speed;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Enemy Name: " << enemy.e_name << ", HP: " << enemy.e_hp <<'\n';
    return os;
}

Enemy:: ~Enemy() {
    std::cout << "U got destructed"<< '\n';
}
