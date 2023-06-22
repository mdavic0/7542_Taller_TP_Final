#ifndef LEFT4DEAD_P90_H
#define LEFT4DEAD_P90_H
#include "Weapon.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"

class P90 : public Weapon {
    public:
        P90();
        void shoot(std::shared_ptr<Collidable>& player, bool right,
                   std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) override;
        void reload() override;
};


#endif //LEFT4DEAD_P90_H
