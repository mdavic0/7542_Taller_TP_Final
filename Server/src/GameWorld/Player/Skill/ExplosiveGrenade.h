#ifndef LEFT4DEAD_EXPLOSIVEGRENADE_H
#define LEFT4DEAD_EXPLOSIVEGRENADE_H

#include "Grenade.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"


class ExplosiveGrenade : public Grenade {
    public:
        explicit ExplosiveGrenade(std::pair<int16_t, int16_t> position);
        void applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                       std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                       double stepTime) override;
        void throwGrenade(std::pair<int16_t, int16_t>& position,
                          double elapsedTime, bool right) override;
        void explode(std::map<uint8_t, std::shared_ptr<Player>> &players,
                     std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                     double stepTime) override;
        ~ExplosiveGrenade() override;
};


#endif //LEFT4DEAD_EXPLOSIVEGRENADE_H
