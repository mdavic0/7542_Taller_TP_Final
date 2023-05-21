#ifndef COMMON_TYPE_GAME_H_
#define COMMON_TYPE_GAME_H_

#include <stdint.h>

enum class TypeGame : int8_t {
    game_idle = 0x00,
    game_survival = 0x01,
    game_clear_zone = 0x02
};

#endif  // COMMON_TYPE_GAME_H_