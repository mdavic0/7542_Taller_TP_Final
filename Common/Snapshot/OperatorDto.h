#ifndef ST_OPERATOR_H_
#define ST_OPERATOR_H_

#include "TypeOperator.h"
#include "State.h"
#include <utility>
#include <map>
#include <string>

class StOperator {
    uint8_t id;
    TypeOperator type;
    State state;
    std::pair<int16_t, int16_t> position;
    uint8_t health;
    uint8_t munition;
    
    public:

    explicit StOperator(const uint8_t& id, const TypeOperator& type, const State& state,
        const std::pair<int16_t, int16_t>& position, const uint8_t& health, const uint8_t& munition);

    uint8_t getId() const;

    TypeOperator getTypeOperator() const;

    State getState() const;

    std::pair<int16_t, int16_t> getPosition() const;

    uint8_t getHealth() const;

    uint8_t getMunition() const;

    //StOperator(StOperator&& other);

    //StOperator& operator=(StOperator&& other);
};

#endif
