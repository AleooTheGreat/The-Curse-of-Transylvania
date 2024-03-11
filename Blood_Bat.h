//
// Created by pasca on 3/11/2024.
//

#ifndef OOP_BLOOD_BAT_H
#define OOP_BLOOD_BAT_H


#include "Enemy.h"

class Blood_Bat: public Enemy {

public:

    ///Constructor
    Blood_Bat(const std::string& name, unsigned int hp, float speed, float damage);

    ///Copy
    Blood_Bat(const Enemy &other1, const Blood_Bat &other);

    ///Destructor
    ~Blood_Bat();
private:
    float bat_damage;
};


#endif //OOP_BLOOD_BAT_H
