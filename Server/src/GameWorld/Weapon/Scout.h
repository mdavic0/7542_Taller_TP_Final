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
        double scope;
        double damageDecreaseByEnemy;

    public:
        Scout();
        bool shoot(std::shared_ptr<Collidable> &player, const bool& right,
                   std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                   const double& stepTime) override;
        bool reload(const double& stepTime) override;

    private:
        void shootRight(std::shared_ptr<Collidable> &player,
                    std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;
        void shootLeft(std::shared_ptr<Collidable> &player,
                   std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;

        double calculateDamage(const double& distance, int& counter);

        std::vector<std::shared_ptr<Infected>> sortEnemiesRight(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds);
        std::vector<std::shared_ptr<Infected>> sortEnemiesLeft(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds);
};


#endif //LEFT4DEAD_SCOUT_H
