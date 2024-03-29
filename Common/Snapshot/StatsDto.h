#ifndef STATS_DTO_H_
#define STATS_DTO_H_

#include <stdint.h>

class StatsDto {
    uint16_t playerId;
    int16_t kills;
    int32_t rankingKills;
    int16_t shots;
    int32_t rankingShots;
    int16_t minutes;
    int16_t seconds;
    int32_t rankingDuration;
    
    public:

    explicit StatsDto(const uint16_t& playerId, const int16_t& kills, const int32_t& rankingKills, const int16_t& shots,
        const int32_t& rankingShots, const int16_t& minutes, const int16_t& seconds, const int32_t& rankingDuration);

    explicit StatsDto(const uint16_t& playerId, const int16_t& kills, const int16_t& shots);

    uint16_t getPlayerId() const;

    int16_t getKills() const;
    
    int16_t getShots() const;
    
    int16_t getMinutes() const;

    int16_t getSeconds() const;

    int32_t getRankingKills() const;

    int32_t getRankingShots() const;

    int32_t getRankingDuration() const;

    void setMinutes(const int16_t& inputMinutes);

    void setSeconds(const int16_t& inputSeconds);

    void setRankingKills(const int32_t& inputRankingKills);

    void setRankingShots(const int32_t& inputRankingShots);

    void setRankingDuration(const int32_t& inputRankingDuration);
};

#endif
