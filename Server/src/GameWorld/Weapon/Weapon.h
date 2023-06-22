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
        uint8_t rate;
        uint8_t capacity;

    protected:
        bool activated;
        uint8_t damage;
        uint8_t munition;
        uint16_t totalFiredBullets;
        double reloadingClock;
    public:
        Weapon();
        Weapon(uint8_t damage, uint8_t rate, uint8_t capacity);
        void activate();
        void deactivate();
        uint8_t& getMunition();
        virtual void shoot(std::shared_ptr<Collidable>& player, bool right,
                           std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) = 0;
        virtual bool reload(double stepTime) = 0;

        virtual ~Weapon();
};


#endif //LEFT4DEAD_WEAPON_H
