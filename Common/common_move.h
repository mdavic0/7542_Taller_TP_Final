#ifndef COMMON_MOVETO_H_
#define COMMON_MOVETO_H_

#include <stdint.h>

enum class MoveTo : int8_t {
    right = 0x00,
    left = 0x01,
    up = 0x02,
    down = 0x03,
    up_right = 0x04,
    up_left = 0x05
    down_right = 0x06;
    down_left = 0x06;
};

#endif  // COMMON_MOVETO_H_