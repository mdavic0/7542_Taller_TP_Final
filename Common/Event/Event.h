#ifndef COMMON_EVENT_H_
#define COMMON_EVENT_H_

#include <stdint.h>

enum class Event : int8_t {
    event_invalid = 0x00,
    event_create = 0x01,
    event_join = 0x02,
    event_start_game = 0x03,
    event_playing = 0x04,
    event_move = 0x05,
    event_stop_move = 0x06,
    event_throw_smoke = 0x07,
    event_stop_smoke = 0x08,
    event_throw_grenade = 0x09,
    event_stop_grenade = 0x10,
    event_blitz_atack = 0x11,
    event_shoot = 0x12,
    event_stop_shoot = 0x13,
    event_leave = 0x14,
    event_end = 0x15,
    event_stats = 0x16,
    event_recharge = 0x17,
    event_reanimate = 0x18,
    event_stop_reanimate = 0x19,
    event_cheat_finish_game = 0x20,
    event_cheat_infinite_munition = 0x21,
    event_cheat_more_velocity = 0x22,
    event_cheat_kill_enemies = 0x23,
    event_cheat_infinite_health = 0x24
};

#endif  // COMMON_EVENT_H_