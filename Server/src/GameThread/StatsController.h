#ifndef STATS_CONTROLLER_H_
#define STATS_CONTROLLER_H_

#include <stdint.h>
#include <vector>
#include <mutex>
#include <memory>
#include "Snapshot.h"

class StatsController {
    private:
    std::vector<int16_t> killsRanking;
    std::vector<int16_t> shotsRanking;
    std::vector<std::pair<int8_t, int8_t>> durationRanking;
    std::string path;
    std::mutex mutex;

    void insertKillsRanking(const int16_t& kills);

    void insertShotsRanking(const int16_t& shots);

    void insertDurationRanking(const std::pair<int8_t, int8_t>& duration);

    uint32_t getKillsIndex(const int16_t& kills);

    uint32_t getShotsIndex(const int16_t& shots);

    uint32_t getDurationIndex(const std::pair<int8_t, int8_t>& duration);

    public:
    /*
     * Constructor público.
     */
    StatsController(const std::string& path);

    std::shared_ptr<Snapshot> updateStats(std::vector<StatsDto> statsFromGame, const int8_t& minutes, const int8_t& seconds);

    ~StatsController();
};

#endif  // STATS_CONTROLLER_H_
