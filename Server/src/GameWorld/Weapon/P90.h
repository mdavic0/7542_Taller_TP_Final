#ifndef LEFT4DEAD_P90_H
#define LEFT4DEAD_P90_H
#include "Weapon.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"

class P90 : public Weapon {
    private:
        int burstFiredBullets;
        bool burstEnded;
        float scope;

    public:
        P90();
        bool shoot(std::shared_ptr<Collidable> &player, const bool& right,
                   std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                   const double& stepTime) override;
        bool reload(const double& stepTime) override;

    private:
        void shootRight(std::shared_ptr<Collidable> &player,
                    std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;
        void shootLeft(std::shared_ptr<Collidable> &player,
                   std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;

        float calculateDamage(const float& distance);
};


#endif //LEFT4DEAD_P90_H
