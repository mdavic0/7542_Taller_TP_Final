#ifndef LEFT4DEAD_TYPEGRENADE_H
#define LEFT4DEAD_TYPEGRENADE_H

#include <stdint.h>

enum class TypeGrenade : int8_t {
    grenade_idle = 0x00,
    grenade_explosive = 0x01,
    grenade_smoke = 0x02
};


#endif //LEFT4DEAD_TYPEGRENADE_H
