#ifndef LEFT4DEAD_SCOUT_H
#define LEFT4DEAD_SCOUT_H
#include "Weapon.h"
#include "Configuration.h"

class Scout : public Weapon {
    public:
        Scout();
        void shoot(bool right) override;
};


#endif //LEFT4DEAD_SCOUT_H
