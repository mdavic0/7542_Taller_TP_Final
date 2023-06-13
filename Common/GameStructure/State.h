#ifndef STATES_H_
#define STATES_H_

#include <stdint.h>

enum class State : uint8_t {
    idle = 0x00,
    moving = 0x01,
    atack = 0x02,
    injure = 0x03,
    hability = 0x04,
    recharge = 0x05,
    dead = 0x06
};

#endif
