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
        double reloadingClock;
        uint8_t rate;
        double shootingClock;
        double rateClock;

    public:
        Weapon();
        Weapon(uint8_t damage, uint8_t rate, uint8_t capacity);
        void activate();
        void deactivate();
        uint8_t& getMunition();
        virtual bool shoot(std::shared_ptr<Collidable> &player, bool right,
                           std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                           double stepTime) = 0;
        virtual bool reload(double stepTime) = 0;

        virtual ~Weapon();

    private:
        virtual void shootRight(std::shared_ptr<Collidable> &player,
                        std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) = 0;
        virtual void shootLeft(std::shared_ptr<Collidable> &player,
                       std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) = 0;


};


#endif //LEFT4DEAD_WEAPON_H
