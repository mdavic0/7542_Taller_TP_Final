#ifndef COMMON_TYPE_OPERATOR_H_
#define COMMON_TYPE_OPERATOR_H_

#include <stdint.h>

enum class TypeOperator : int8_t {
    operator_idle = 0x00,
    operator_idf = 0x01,
    operator_p90 = 0x02,
    operator_scout = 0x03
};

#endif  // COMMON_TYPE_OPERATOR_H_