#ifndef COMMON_COMMAND_H_
#define COMMON_COMMAND_H_

#include <stdint.h>

enum class Command : int8_t {
    command_invalid = 0x00,
    command_create = 0x01,
    command_join = 0x02,
    command_broadcast = 0x03,
    command_read = 0x04,
    command_leave = 0x05
};

#endif  // COMMON_COMMAND_H_
