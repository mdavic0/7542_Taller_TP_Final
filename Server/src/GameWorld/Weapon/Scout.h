#ifndef LEFT4DEAD_SCOUT_H
#define LEFT4DEAD_SCOUT_H
#include "Weapon.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"

class Scout : public Weapon {
    private:
        int burstFiredBullets;
        bool burstEnded;

    public:
        Scout();
        bool shoot(std::shared_ptr<Collidable> &player, bool right,
                   std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                   double stepTime) override;
        bool reload(double stepTime) override;

    private:
        void shootRight(std::shared_ptr<Collidable> &player,
                    std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) override;
        void shootLeft(std::shared_ptr<Collidable> &player,
                   std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) override;
};


#endif //LEFT4DEAD_SCOUT_H
