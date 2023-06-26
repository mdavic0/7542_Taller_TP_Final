#include "StatsDto.h"

StatsDto::StatsDto(const int8_t& playerId, const uint16_t& kills, const uint32_t& rankingKills,
    const uint16_t shots, const uint32_t& rankingShots, const uint8_t& minutes, const uint8_t& seconds,
    const uint32_t& rankingDuration) : playerId(playerId), kills(kills), rankingKills(rankingKills),
    shots(shots), rankingShots(rankingShots), minutes(minutes), seconds(seconds), rankingDuration(rankingDuration) {}

StatsDto::StatsDto(const int8_t& playerId, const uint16_t& kills, const uint16_t shots) : playerId(playerId),
    kills(kills), rankingKills(0), shots(shots), rankingShots(0), minutes(0), seconds(0), rankingDuration(0) {}

int8_t StatsDto::getPlayerId() const {
    return playerId;
}

uint16_t StatsDto::getKills() const {
    return kills;
}

uint16_t StatsDto::getShots() const {
    return shots;
}

uint8_t StatsDto::getMinutes() const {
    return minutes;
}

uint8_t StatsDto::getSeconds() const {
    return seconds;
}

uint32_t StatsDto::getRankingKills() const {
    return rankingKills;
}

uint32_t StatsDto::getRankingShots() const {
    return rankingShots;
}

uint32_t StatsDto::getRankingDuration() const {
    return rankingDuration;
}

void StatsDto::setMinutes(const uint8_t& inputMinutes) {
    minutes = inputMinutes;
}

void StatsDto::setSeconds(const uint8_t& inputSeconds) {
    seconds = inputSeconds;
}

void StatsDto::setRankingKills(const uint32_t& inputRankingKills) {
    rankingKills = inputRankingKills;
}

void StatsDto::setRankingShots(const uint32_t& inputRankingShots) {
    rankingShots = inputRankingShots;
}

void StatsDto::setRankingDuration(const uint32_t& inputRankingDuration) {
    rankingDuration = inputRankingDuration;
}