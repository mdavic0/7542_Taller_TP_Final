#ifndef STATS_DTO_H_
#define STATS_DTO_H_

#include <stdint.h>

class StatsDto {
    uint8_t playerId; // IF PlayerId < 0 is a player of external game
    uint16_t kills;
    uint16_t shots;
    float duration;
    
    public:

    explicit StatsDto(const uint8_t& playerId, const uint16_t& kills, const uint16_t shots, const float& duration);

    uint8_t getPlayerId() const;

    uint16_t getKills() const;
    
    uint16_t getShots() const;
    
    float getDuration() const;

};

#endif
