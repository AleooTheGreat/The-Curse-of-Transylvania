//
// Created by pasca on 3/11/2024.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H


#include <string>

class Enemy {
public:

    ///Constructors
    explicit Enemy(std::string name, unsigned int hp, float speed);

    ///Copy
    Enemy(const Enemy& other);
    Enemy& operator=(const Enemy& other);

    ///Other
    friend std::ostream& operator<<(std::ostream& os, const Enemy& Enemy);

    ///Destroy(Mosh Pit)
    ~Enemy();



private:
    std::string e_name;
    unsigned int e_hp{};
    float e_speed{};

};


#endif //OOP_ENEMY_H
