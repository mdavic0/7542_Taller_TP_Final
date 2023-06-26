#ifndef STATS_DTO_H_
#define STATS_DTO_H_

#include <stdint.h>

class StatsDto {
    int8_t playerId; // IF PlayerId < 0 is a player of external game
    uint16_t kills;
    uint32_t rankingKills;
    uint16_t shots;
    uint32_t rankingShots;
    uint8_t minutes;
    uint8_t seconds;
    uint32_t rankingDuration;
    
    public:

    explicit StatsDto(const int8_t& playerId, const uint16_t& kills, const uint32_t& rankingKills, const uint16_t shots,
        const uint32_t& rankingShots, const uint8_t& minutes, const uint8_t& seconds, const uint32_t& rankingDuration);


    explicit StatsDto(const int8_t& playerId, const uint16_t& kills, const uint16_t shots);

    int8_t getPlayerId() const;

    uint16_t getKills() const;
    
    uint16_t getShots() const;
    
    uint8_t getMinutes() const;

    uint8_t getSeconds() const;

    uint32_t getRankingKills() const;

    uint32_t getRankingShots() const;

    uint32_t getRankingDuration() const;

    void setMinutes(const uint8_t& inputMinutes);

    void setSeconds(const uint8_t& inputSeconds);

    void setRankingKills(const uint32_t& inputRankingKills);

    void setRankingShots(const uint32_t& inputRankingShots);

    void setRankingDuration(const uint32_t& inputRankingDuration);
};

#endif
