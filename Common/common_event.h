#ifndef COMMON_EVENT_H_
#define COMMON_EVENT_H_

#include <stdint.h>

enum class Event : int8_t {
    event_invalid = 0x00,
    event_create = 0x01,
    event_join = 0x02,
    event_move = 0x03,
    event_stop_move = 0x04,
    event_leave = 0x05,
    event_playing = 0x06,
    event_start_game = 0x07
};

#endif  // COMMON_EVENT_H_