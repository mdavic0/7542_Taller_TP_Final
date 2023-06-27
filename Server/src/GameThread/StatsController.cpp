#include "StatsController.h"
#include <algorithm>
#include <ostream>
#include <fstream>
#include <filesystem>
#include "Defines.h"


StatsController::StatsController(const std::string& path) : path(path) {
    std::ifstream file(path);
    if (file.is_open()) {
        std::string header;
        int16_t value;
        while (file >> header && header != HEADER_END) {
            if (header == HEADER_KILL) {
                while (file >> value && value != -1) {
                    killsRanking.push_back(value);
                }
            } else if (header == HEADER_SHOT) {
                while (file >> value && value != -1) {
                    shotsRanking.push_back(value);
                }
            } else if (header == HEADER_DURATION) {
                int16_t value1, value2;
                while (file >> value1 >> value2 && value1 != -1 && value2 != -1) {
                    durationRanking.push_back({value1, value2});
                }
            }
        }
        file.close();
    }
}

void StatsController::insertKillsRanking(const int16_t& kills) {
    auto it = std::lower_bound(killsRanking.begin(), killsRanking.end(), kills, [](const int16_t& a, const int16_t& b) {
        return a > b; 
    });
    killsRanking.insert(it, kills);
}

void StatsController::insertShotsRanking(const int16_t& shots) {
    auto it = std::lower_bound(shotsRanking.begin(), shotsRanking.end(), shots, [](const int16_t& a, const int16_t& b) {
        return a > b; 
    });
    shotsRanking.insert(it, shots);
}

void StatsController::insertDurationRanking(const std::pair<int16_t, int16_t>& duration) {
    auto it = std::lower_bound(durationRanking.begin(), durationRanking.end(), duration, [](const std::pair<int16_t, int16_t>& a, const std::pair<int16_t, int16_t>& b) {
            int totalSecondsA = a.first * 60 + a.second;
            int totalSecondsB = b.first * 60 + b.second;
            return totalSecondsA > totalSecondsB;
        });
    durationRanking.insert(it, duration);
}

uint32_t StatsController::getKillsIndex(const int16_t& kills) {
    for (uint i = 0; i < killsRanking.size(); i++) {
        if (killsRanking[i] == kills) {
            return i;
        }
    }
    return -1;
}

uint32_t StatsController::getShotsIndex(const int16_t& shots) {
    for (uint i = 0; i < shotsRanking.size(); i++) {
        if (shotsRanking[i] == shots) {
            return i;
        }
    }
    return -1;
}

uint32_t StatsController::getDurationIndex(const std::pair<int16_t, int16_t>& duration) {
    for (uint i = 0; i < durationRanking.size(); i++) {
        if (durationRanking[i] == duration) {
            return i;
        }
    }
    return -1;
}

std::shared_ptr<Snapshot> StatsController::updateStats(std::vector<StatsDto>& statsFromGame,
    const int16_t& minutes, const int16_t& seconds) {
    std::lock_guard<std::mutex> locker(mutex);

    std::pair<int16_t, int16_t> duration({minutes, seconds});
    insertDurationRanking(duration);
    int32_t indexDuration = getDurationIndex(duration);

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

StatsController::~StatsController() {
    std::ofstream file(path);
    if (file.is_open()) {
        // SAVE KILLS
        file << HEADER_KILL << std::endl;
        for (const auto& value : killsRanking) {
            file << value << " ";
        }
        file << "-1" << std::endl; 

        // SAVE SHOTS
        file << HEADER_SHOT << std::endl;
        for (const auto& value : shotsRanking) {
            file << value << " ";
        }
        file << "-1" << std::endl; 

        // SAVE DURATION
        file << HEADER_DURATION << std::endl;
        for (const auto& value : durationRanking) {
            file << value.first << " " << value.second << " ";
        }
        file << "-1 -1" << std::endl; 

        file << HEADER_END << std::endl;

        file.close();
    }
}
