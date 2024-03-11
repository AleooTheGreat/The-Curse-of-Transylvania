//
// Created by pasca on 3/11/2024.
//

#pragma once
#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H


#include <string>

class Player{
public:
    ///Constructor
    explicit Player(std::string  name = "Default", unsigned int hp = 100,float speed = 1.0f, float power = 1.0f);

    ///Copy
    Player(const Player& other);
    Player& operator=(const Player& other);

    ///Other
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    ///Destroy(Mosh Pit)
    ~Player();

private:
    std::string m_name;
    unsigned int m_hp;
    float m_speed;
    float m_power;
};


#endif //OOP_PLAYER_H