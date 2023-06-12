#ifndef LEFT4DEAD_RESPAWNCONTROLLER_H
#define LEFT4DEAD_RESPAWNCONTROLLER_H
#include <vector>
#include <cstdint>

class RespawnController {
    private:
        std::vector<std::pair<int16_t, int16_t>> playerAvailablePositions;
        std::vector<std::pair<int16_t, int16_t>> infectedAvailablePositions;
        std::vector<std::pair<int16_t, int16_t>> obstacleAvailablePositions;

    public:
        RespawnController();

        // POST: Returns random respawn position
        std::pair<int16_t, int16_t> getPlayerRespawnPosition();
        std::pair<int16_t, int16_t> getInfectedRespawnPosition();
        std::pair<int16_t, int16_t> getObstacleRespawnPosition();

    private:
        // POST: Reload the respawn positions (usefull when trying to
        //      reset a round or spawning new infecteds)
        void resetRespawns();

        // POST: Load / create the respanw positions
        void createPlayerRespawns();
        void createInfectedRespawns();
        void createObstacleRespawns();
};


#endif //LEFT4DEAD_RESPAWNCONTROLLER_H
