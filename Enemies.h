//
// Created by pasca on 3/10/2024.
//

#ifndef OOP_ENEMIES_H
#define OOP_ENEMIES_H


#include <iosfwd>

class Enemies {
public:
    ///Constructor
    explicit Enemies(unsigned int type);

    //Copy
    Enemies(const Enemies& other);
    Enemies& operator=(const Enemies& other);

    ///Other
    friend std::ostream& operator<<(std::ostream& os, const Enemies& Enemies);

    ///Destroy(Mosh Pit)
    ~Enemies();

private:
    unsigned int E_type;
};


#endif //OOP_ENEMIES_H
