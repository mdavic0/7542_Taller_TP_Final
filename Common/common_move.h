#ifndef COMMON_MOVETO_H_
#define COMMON_MOVETO_H_

#include <stdint.h>

enum class MoveTo : int8_t {
    move_right = 0x00,
    move_left = 0x01,
    move_up = 0x02,
    move_down = 0x03,
    move_up_right = 0x04,
    move_up_left = 0x05,
    move_down_right = 0x06,
    move_down_left = 0x06,
    move_not = 0x07
};

#endif  // COMMON_MOVETO_H_