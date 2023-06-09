#ifndef LEFT4DEAD_TYPEINFECTED_H
#define LEFT4DEAD_TYPEINFECTED_H

#include <stdint.h>

enum class TypeInfected : int8_t {
    infected_zombie = 0x00,
    infected_jumper = 0x01,
    infected_witch = 0x02,
    infected_spear = 0x03,
    infected_venom = 0x04
};

#endif //LEFT4DEAD_TYPEINFECTED_H
