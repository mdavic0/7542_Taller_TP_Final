#ifndef LEFT4DEAD_WEAPON_H
#define LEFT4DEAD_WEAPON_H
#include "Event.h"
#include "TypeOperator.h"

class Weapon {
    private:
        uint8_t damage;
        uint8_t rate;
        uint8_t capacity;
    public:
        Weapon();
        Weapon(uint8_t damage, uint8_t rate, uint8_t capacity);
        virtual void shoot(Event event/*,List of zombies*/) = 0;
        virtual ~Weapon();
};


#endif //LEFT4DEAD_WEAPON_H
