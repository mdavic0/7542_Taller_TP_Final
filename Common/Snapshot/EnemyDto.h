#ifndef ENEMY_DTO_H_
#define ENEMY_DTO_H_

#include <utility>
#include <map>
#include <string>
#include "State.h"
#include "TypeInfected.h"

class EnemyDto {
    uint16_t id;
    TypeInfected type;
    State state;
    std::pair<int16_t, int16_t> position;
    
    public:

    explicit EnemyDto(const uint16_t& id, const TypeInfected& type, const State& state,
        const std::pair<int16_t, int16_t>& position);

    uint16_t getId() const;

    TypeInfected getTypeInfected() const;

    State getState() const;

    std::pair<int16_t, int16_t> getPosition() const;
};

#endif
