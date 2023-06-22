#ifndef LEFT4DEAD_TYPEDIFFICULTY_H
#define LEFT4DEAD_TYPEDIFFICULTY_H

#include <stdint.h>

enum class TypeDifficulty : int8_t {
    difficulty_idle = 0x00,
    difficulty_easy = 0x01,
    difficulty_normal = 0x02,
    difficulty_hard = 0x03,
    difficulty_god = 0x04
};


#endif //LEFT4DEAD_TYPEDIFFICULTY_H
