#ifndef STATS_DTO_H_
#define STATS_DTO_H_

#include <stdint.h>

class StatsDto {
    int8_t playerId; // IF PlayerId < 0 is a player of external game
    int16_t kills;
    int32_t rankingKills;
    int16_t shots;
    int32_t rankingShots;
    int8_t minutes;
    int8_t seconds;
    int32_t rankingDuration;
    
    public:

    explicit StatsDto(const int8_t& playerId, const int16_t& kills, const int32_t& rankingKills, const int16_t shots,
        const int32_t& rankingShots, const int8_t& minutes, const int8_t& seconds, const int32_t& rankingDuration);

    explicit StatsDto(const int8_t& playerId, const int16_t& kills, const int16_t shots);

    int8_t getPlayerId() const;

    int16_t getKills() const;
    
    int16_t getShots() const;
    
    int8_t getMinutes() const;

    int8_t getSeconds() const;

    int32_t getRankingKills() const;

    int32_t getRankingShots() const;

    int32_t getRankingDuration() const;

    void setMinutes(const int8_t& inputMinutes);

    void setSeconds(const int8_t& inputSeconds);

    void setRankingKills(const int32_t& inputRankingKills);

    void setRankingShots(const int32_t& inputRankingShots);

    void setRankingDuration(const int32_t& inputRankingDuration);
};

#endif
