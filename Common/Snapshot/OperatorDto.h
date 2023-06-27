#ifndef ST_OPERATOR_H_
#define ST_OPERATOR_H_

#include "TypeOperator.h"
#include "State.h"
#include <utility>
#include <map>
#include <string>

class StOperator {
    uint16_t id;
    TypeOperator type;
    State state;
    std::pair<int16_t, int16_t> position;
    int16_t health;
    uint8_t munition;
    bool grenadeAvailable;
    bool smokeAvailable;
    
    public:

    explicit StOperator(const uint16_t& id, const TypeOperator& type, const State& state,
        const std::pair<int16_t, int16_t>& position, const int16_t& health, const uint8_t& munition,
        const bool& grenadeAvailable, const bool& smokeAvailable);

    uint16_t getId() const;

    TypeOperator getTypeOperator() const;

    State getState() const;

    std::pair<int16_t, int16_t> getPosition() const;

    int16_t getHealth() const;

    uint8_t getMunition() const;

    bool isGrenadeAvailable() const;
    
    bool isSmokeAvailable() const;

    //StOperator(StOperator&& other);

    //StOperator& operator=(StOperator&& other);
};

#endif
