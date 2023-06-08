#ifndef LEFT4DEAD_WEAPON_H
#define LEFT4DEAD_WEAPON_H
#include "Event.h"
#include "TypeOperator.h"

class Weapon {
    private:
        uint8_t damage;
        uint8_t rate;
        uint8_t capacity;
protected:
    bool activated;
public:
        Weapon();
        Weapon(uint8_t damage, uint8_t rate, uint8_t capacity);
        void activate();
        void deactivate();
        virtual void shoot(bool right/*,List of zombies*/) = 0;
        virtual ~Weapon();
};


#endif //LEFT4DEAD_WEAPON_H
