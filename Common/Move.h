#ifndef COMMON_MOVETO_H_
#define COMMON_MOVETO_H_

#include <cstdint>

enum class MoveTo : int8_t {
    move_idle = 0x00,
    move_right = 0x01,
    move_left = 0x02,
    move_up = 0x03,
    move_down = 0x04,
};

#endif
