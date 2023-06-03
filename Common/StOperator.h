#ifndef ST_OPERATOR_H_
#define ST_OPERATOR_H_

#include "TypeOperator.h"
#include "State.h"
#include <utility>

class StOperator {
    uint8_t id;
    TypeOperator type;
    State state;
    std::pair<uint16_t, uint16_t> position;
    uint8_t health;
    
    public:

    explicit StOperator(const uint8_t& id, const TypeOperator& type, const State& state,
        const std::pair<uint16_t, uint16_t>& position, const uint8_t& health);

    uint8_t getId() const;

    TypeOperator getTypeOperator() const;

    State getState() const;

    std::pair<uint16_t, uint16_t> getPosition() const;

    uint8_t getHealth() const;

    //StOperator(StOperator&& other);

    //StOperator& operator=(StOperator&& other);
};

#endif
