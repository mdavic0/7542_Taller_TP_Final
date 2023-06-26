#include "StatsDto.h"

StatsDto::StatsDto(const uint8_t& playerId, const uint16_t& kills, const uint16_t shots, const float& duration) :
    playerId(playerId), kills(kills), shots(shots), duration(duration) {}

uint8_t StatsDto::getPlayerId() const {
    return playerId;
}

uint16_t StatsDto::getKills() const {
    return kills;
}

uint16_t StatsDto::getShots() const {
    return shots;
}

float StatsDto::getDuration() const {
    return duration;
}
