#include "RespawnController.h"
#include <random>
#include <functional>
#include <iterator>
#include <utility>
#include "Defines.h"

#include <iostream>
RespawnController::RespawnController() : playerAvailablePositions(),
   infectedAvailablePositions(), obstacleAvailablePositions() {
    this->resetRespawns();
}

std::pair<int16_t, int16_t> RespawnController::getPlayerRespawnPosition() {
    std::random_device dev;
    std::mt19937_64 rng(dev());

    std::uniform_int_distribution<size_t> idDist(0, playerAvailablePositions.size() - 1);
    auto elementId = playerAvailablePositions.begin();
    std::advance(elementId, idDist(rng));

    auto pos = elementId;
    playerAvailablePositions.erase(elementId);

    return *pos;
    //return playerAvailablePositions.front();
}

std::pair<int16_t, int16_t> RespawnController::getInfectedRespawnPosition() {
    std::random_device dev;
    std::mt19937_64 rng(dev());

    std::uniform_int_distribution<size_t> idDist(0, infectedAvailablePositions.size() - 1);
    auto elementId = infectedAvailablePositions.begin();
    std::advance(elementId, idDist(rng));

    auto pos = elementId;
    infectedAvailablePositions.erase(elementId);

    return *pos;
    //return infectedAvailablePositions.front();
}

std::pair<int16_t, int16_t> RespawnController::getObstacleRespawnPosition() {
    std::random_device dev;
    std::mt19937_64 rng(dev());

    std::uniform_int_distribution<size_t> idDist(0, obstacleAvailablePositions.size() - 1);
    auto elementId = obstacleAvailablePositions.begin();
    std::advance(elementId, idDist(rng));

    auto pos = elementId;
    obstacleAvailablePositions.erase(elementId);

    return *pos;
    //return obstacleAvailablePositions.front();
}

void RespawnController::resetRespawns() {
    this->createInfectedRespawns();
    this->createPlayerRespawns();
    this->createObstacleRespawns();
}

void RespawnController::createPlayerRespawns() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH / 2)  - (SIZE_SPRITE_X) + (SIZE_SPRITE_X * i),
                                                    (MAP_HEIGTH * 4 / 5) - (SIZE_SPRITE_Y) + ((SIZE_SPRITE_Y / 2) * j)};
            playerAvailablePositions.push_back(position);
        }
    }
}

void RespawnController::createInfectedRespawns() {
    // LEFT SIDE OF THE SCREEN
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 5; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH / 32) + ((SIZE_SPRITE_X / 2) * i),
                                                    ((MAP_HEIGTH * 4) / 5) - (SIZE_SPRITE_Y) + ((SIZE_SPRITE_Y / 2) * j)};
            infectedAvailablePositions.push_back(position);
        }
    }

    // RIGHT SIDE OF THE SCREEN
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 5; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH * 3 / 4) + ((SIZE_SPRITE_X / 2) * i),
                                                    ((MAP_HEIGTH * 4) / 5) + ((SIZE_SPRITE_Y / 2) * j)};
            infectedAvailablePositions.push_back(position);
        }
    }
}

void RespawnController::createObstacleRespawns() {
    // LEFT SIDE OF THE SCREEN
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH / 4) + ((SIZE_SPRITE_X) * i),
                                                    ((MAP_HEIGTH * 4) / 5) + ((SIZE_SPRITE_Y) * j)};
            obstacleAvailablePositions.push_back(position);
        }
    }

    // RIGHT SIDE OF THE SCREEN
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH * 3 / 5) + ((SIZE_SPRITE_X / 2) * i),
                                                    ((MAP_HEIGTH * 4) / 5) + ((SIZE_SPRITE_Y / 2) * j)};
            obstacleAvailablePositions.push_back(position);
        }
    }
}
