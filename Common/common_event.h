#ifndef COMMON_EVENT_H_
#define COMMON_EVENT_H_

#include <stdint.h>

enum class Event : int8_t {
    event_invalid = 0x00,
    event_create = 0x01,
    event_join = 0x02,
    event_broadcast = 0x03,
    event_read = 0x04,
    event_leave = 0x05,
    event_move = 0x06
};

#endif  // COMMON_EVENT_H_