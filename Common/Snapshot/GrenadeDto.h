#ifndef GRENADE_DTO_H_
#define GRENADE_DTO_H_

#include <utility>
#include <string>
#include "TypeGrenade.h"

class GrenadeDto {
    TypeGrenade type;
    std::pair<int16_t, int16_t> position;
    bool exploded;
    
    public:

    explicit GrenadeDto(const bool& exploded, const TypeGrenade& type,
        const std::pair<int16_t, int16_t>& position);

    bool alreadyExploded() const;

    TypeGrenade getTypeGrenade() const;

    std::pair<int16_t, int16_t> getPosition() const;

};

#endif
