#ifndef LEFT4DEAD_WEAPON_H
#define LEFT4DEAD_WEAPON_H
#include "Event.h"
#include "TypeOperator.h"
#include <map>
#include <memory>
#include "Infected.h"

class Infected;

class Weapon {
    private:
        uint8_t capacity;

    protected:
        bool activated;
        uint8_t damage;
        uint8_t munition;
        uint16_t totalFiredBullets;
        uint16_t kills;
        double reloadingClock;
        uint8_t rate;
        double shootingClock;
        double rateClock;

    public:
        Weapon();
        Weapon(const uint8_t& damage, const uint8_t& rate, const uint8_t& capacity);
        void activate();
        void deactivate();
        uint8_t& getMunition();
        uint16_t& getKills();
        uint16_t& getShots();
        virtual bool shoot(std::shared_ptr<Collidable> &player, const bool& right,
                           std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                           const double& stepTime) = 0;
        virtual bool reload(const double& stepTime) = 0;

        virtual ~Weapon();

    private:
        virtual void shootRight(std::shared_ptr<Collidable> &player,
                        std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) = 0;
        virtual void shootLeft(std::shared_ptr<Collidable> &player,
                       std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) = 0;
};


#endif //LEFT4DEAD_WEAPON_H
