#ifndef LEFT4DEAD_SCOUT_H
#define LEFT4DEAD_SCOUT_H
#include "Weapon.h"

class Scout : public Weapon {
public:
    Scout();
    void shoot(Event event) override;
};


#endif //LEFT4DEAD_SCOUT_H
