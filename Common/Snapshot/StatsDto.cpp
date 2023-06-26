#include "StatsDto.h"

StatsDto::StatsDto(const int8_t& playerId, const int16_t& kills, const int32_t& rankingKills,
    const int16_t shots, const int32_t& rankingShots, const int16_t& minutes, const int16_t& seconds,
    const int32_t& rankingDuration) : playerId(playerId), kills(kills), rankingKills(rankingKills),
    shots(shots), rankingShots(rankingShots), minutes(minutes), seconds(seconds), rankingDuration(rankingDuration) {}

StatsDto::StatsDto(const int8_t& playerId, const int16_t& kills, const int16_t shots) : playerId(playerId),
    kills(kills), rankingKills(0), shots(shots), rankingShots(0), minutes(0), seconds(0), rankingDuration(0) {}

int8_t StatsDto::getPlayerId() const {
    return playerId;
}

int16_t StatsDto::getKills() const {
    return kills;
}

int16_t StatsDto::getShots() const {
    return shots;
}

int16_t StatsDto::getMinutes() const {
    return minutes;
}

int16_t StatsDto::getSeconds() const {
    return seconds;
}

int32_t StatsDto::getRankingKills() const {
    return rankingKills;
}

int32_t StatsDto::getRankingShots() const {
    return rankingShots;
}

int32_t StatsDto::getRankingDuration() const {
    return rankingDuration;
}

void StatsDto::setMinutes(const int16_t& inputMinutes) {
    minutes = inputMinutes;
}

void StatsDto::setSeconds(const int16_t& inputSeconds) {
    seconds = inputSeconds;
}

void StatsDto::setRankingKills(const int32_t& inputRankingKills) {
    rankingKills = inputRankingKills;
}

void StatsDto::setRankingShots(const int32_t& inputRankingShots) {
    rankingShots = inputRankingShots;
}

void StatsDto::setRankingDuration(const int32_t& inputRankingDuration) {
    rankingDuration = inputRankingDuration;
}
