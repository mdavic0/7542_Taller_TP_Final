#ifndef STATS_CONTROLLER_H_
#define STATS_CONTROLLER_H_

#include <stdint.h>
#include <vector>
#include <mutex>
#include <memory>
#include "Snapshot.h"

class StatsController {
    private:
    std::vector<uint16_t> killsRanking;
    std::vector<uint16_t> shotsRanking;
    std::vector<std::pair<int8_t, int8_t>> durationRanking;
    std::mutex mutex;

    void insertKillsRanking(const uint16_t& kills);

    void insertShotsRanking(const uint16_t& shots);

    void insertDurationRanking(const std::pair<int8_t, int8_t>& duration);

    uint32_t getKillsIndex(const uint16_t& kills);

    uint32_t getShotsIndex(const uint16_t& shots);

    uint32_t getDurationIndex(const std::pair<int8_t, int8_t>& duration);

    public:
    /*
     * Constructor público.
     */
    StatsController();

    std::shared_ptr<Snapshot> updateStats(std::vector<StatsDto> statsFromGame, const uint8_t& minutes, const uint8_t& seconds);

    ~StatsController();
};

#endif  // STATS_CONTROLLER_H_
