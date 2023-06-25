#ifndef LEFT4DEAD_SMOKEGRENADE_H
#define LEFT4DEAD_SMOKEGRENADE_H

#include "Grenade.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"


class SmokeGrenade : public Grenade {
    public:
        explicit SmokeGrenade(std::pair<int16_t, int16_t> position);
        void applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                       std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                       double stepTime) override;
        void throwGrenade(std::pair<int16_t, int16_t>& position,
                          double elapsedTime, bool right) override;

        ~SmokeGrenade() override;
};


#endif //LEFT4DEAD_SMOKEGRENADE_H
