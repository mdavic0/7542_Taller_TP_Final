#ifndef LEFT4DEAD_P90_H
#define LEFT4DEAD_P90_H
#include "Weapon.h"

class P90 : public Weapon {
public:
    P90();
    void shoot(bool right) override;
};


#endif //LEFT4DEAD_P90_H