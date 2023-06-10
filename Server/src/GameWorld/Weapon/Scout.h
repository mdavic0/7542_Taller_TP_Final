#ifndef LEFT4DEAD_SCOUT_H
#define LEFT4DEAD_SCOUT_H
#include "Weapon.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"

class Scout : public Weapon {
    public:
        Scout();
        void shoot(std::shared_ptr<Collidable>& player, bool right,
                   std::map<int, std::shared_ptr<Infected>>& infecteds) override;
};


#endif //LEFT4DEAD_SCOUT_H
