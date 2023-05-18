#ifndef COMMON_MOVETO_H_
#define COMMON_MOVETO_H_

#include <stdint.h>

enum class MoveTo : int8_t {
    move_not = 0x00,
    move_right = 0x01,
    move_left = 0x02,
    move_up = 0x03,
    move_down = 0x04,
    move_up_right = 0x05,
    move_up_left = 0x06,
    move_down_right = 0x07,
    move_down_left = 0x08
};

#endif  // COMMON_MOVETO_H_