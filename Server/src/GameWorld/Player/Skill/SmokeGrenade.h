#ifndef LEFT4DEAD_SMOKEGRENADE_H
#define LEFT4DEAD_SMOKEGRENADE_H

#include "Grenade.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"


class SmokeGrenade : public Grenade {
    private:
        double speedReduction;

    public:
        explicit SmokeGrenade(const std::pair<int16_t, int16_t>& position, const uint16_t& id);
        void applyStep(std::map<uint16_t, std::shared_ptr<Player>> &players,
                       std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                       const double& stepTime) override;
        void throwGrenade(const std::pair<int16_t, int16_t>& position,
                          const double& elapsedTime, const bool& right) override;
        void explode(std::map<uint16_t, std::shared_ptr<Player>> &players,
                     std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                     const double& stepTime) override;
        ~SmokeGrenade() override;
};


#endif //LEFT4DEAD_SMOKEGRENADE_H
