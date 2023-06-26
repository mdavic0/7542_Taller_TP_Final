#include "StatsController.h"
#include <algorithm>

StatsController::StatsController() {}

void StatsController::insertKillsRanking(const uint16_t& kills) {
    auto it = std::lower_bound(killsRanking.begin(), killsRanking.end(), kills);
    killsRanking.insert(it, kills);
}

void StatsController::insertShotsRanking(const uint16_t& shots) {
    auto it = std::lower_bound(shotsRanking.begin(), shotsRanking.end(), shots);
    shotsRanking.insert(it, shots);
}

void StatsController::insertDurationRanking(const std::pair<int8_t, int8_t>& duration) {
    auto it = std::lower_bound(durationRanking.begin(), durationRanking.end(), duration, [](const std::pair<int8_t, int8_t>& a, const std::pair<int8_t, int8_t>& b) {
            return a.second < b.second;
        });
    durationRanking.insert(it, duration);
}

uint32_t StatsController::getKillsIndex(const uint16_t& kills) {
    auto it = std::lower_bound(killsRanking.begin(), killsRanking.end(), kills);
    return std::distance(killsRanking.begin(), it);
}

uint32_t StatsController::getShotsIndex(const uint16_t& shots) {
    auto it = std::lower_bound(shotsRanking.begin(), shotsRanking.end(), shots);
    return std::distance(shotsRanking.begin(), it);
}

uint32_t StatsController::getDurationIndex(const std::pair<int8_t, int8_t>& duration) {
    auto it = std::lower_bound(durationRanking.begin(), durationRanking.end(), duration, [](const std::pair<int8_t, int8_t>& a, const std::pair<int8_t, int8_t>& b) {
            return a.second < b.second;
        });
    return std::distance(durationRanking.begin(), it);
}

std::shared_ptr<Snapshot> StatsController::updateStats(std::vector<StatsDto> statsFromGame,
    const uint8_t& minutes, const uint8_t& seconds) {
    std::lock_guard<std::mutex> locker(mutex);

    std::pair<int8_t, int8_t> duration({minutes, seconds});
    insertDurationRanking(duration);
    uint32_t indexDuration = getDurationIndex(duration);

    for (auto& stats : statsFromGame) {
        insertKillsRanking(stats.getKills());
        insertShotsRanking(stats.getShots());
    }

    // GET INDEX AFTER INSERT ALL PLAYERS STATS
    for (auto& stats : statsFromGame) {
        stats.setMinutes(minutes);
        stats.setSeconds(seconds);
        stats.setRankingDuration(indexDuration);
        stats.setRankingShots(getShotsIndex(stats.getShots()));
        stats.setRankingKills(getKillsIndex(stats.getKills()));
    }

    return std::make_shared<Snapshot>(statsFromGame);
}


StatsController::~StatsController() {}