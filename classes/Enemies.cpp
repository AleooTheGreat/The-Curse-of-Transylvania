//
// Created by pasca on 3/10/2024.
//

#include <iostream>
#include "../header/Enemies.h"

Enemies::Enemies(unsigned int type): E_type{type}{
    std::cout<< "Enemies a fost creeat" << '\n';
}

Enemies::Enemies(const Enemies& other):E_type{other.E_type}{
    std::cout << "Enemyies fost apelat" << '\n';
}

Enemies&Enemies::operator=(const Enemies& other) {
   E_type = other.E_type;
   return *this;
}

std::ostream& operator<<(std::ostream& os, const Enemies& Enemies) {
    os << "Enemies Type: " << Enemies.E_type << '\n';
    return os;
}

Enemies:: ~Enemies() {
    std::cout << "U got destructed"<< '\n';
}