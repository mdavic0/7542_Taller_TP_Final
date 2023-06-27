#ifndef LEFT4DEAD_IDF_H
#define LEFT4DEAD_IDF_H
#include "Weapon.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"

class Idf : public Weapon {
    private:
        int burstFiredBullets;
        bool burstEnded;
        float scope;

    public:
        Idf();
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


#endif //LEFT4DEAD_IDF_H
