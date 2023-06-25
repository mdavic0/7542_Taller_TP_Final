#include "GrenadeDto.h"

GrenadeDto::GrenadeDto(const bool& exploded, const TypeGrenade& type,
          const std::pair<int16_t, int16_t>& position) : type(type),
          position(position), exploded(exploded) {}

bool GrenadeDto::alreadyExploded() const {
     return exploded;
}

TypeGrenade GrenadeDto::getTypeGrenade() const {
     return type;
}

std::pair<int16_t, int16_t> GrenadeDto::getPosition() const {
     return position;
}