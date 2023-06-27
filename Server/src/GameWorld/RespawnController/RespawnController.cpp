#include "RespawnController.h"
#include <random>
#include <functional>
#include <iterator>
#include <utility>
#include "Defines.h"


RespawnController::RespawnController() : playerAvailablePositions(),
   infectedAvailablePositions(), obstacleAvailablePositions() {
    this->resetRespawns();
}

std::pair<int16_t, int16_t> RespawnController::getPlayerRespawnPosition() {
    std::random_device dev;
    std::mt19937_64 rng(dev());

    std::uniform_int_distribution<size_t> idDist(0, playerAvailablePositions.size() - 1);
    //auto elementId = playerAvailablePositions.begin();
    //std::advance(elementId, idDist(rng));

    //auto pos = *elementId;
    //playerAvailablePositions.erase(elementId);
    std::size_t randomIndex = idDist(rng);
    auto pos = playerAvailablePositions[randomIndex];
    playerAvailablePositions.erase(playerAvailablePositions.begin() + randomIndex);
    return pos;
}

std::pair<int16_t, int16_t> RespawnController::getInfectedRespawnPosition() {
    std::random_device dev;
    std::mt19937_64 rng(dev());

    std::uniform_int_distribution<size_t> idDist(0, infectedAvailablePositions.size() - 1);
    //auto elementId = infectedAvailablePositions.begin();
    //std::advance(elementId, idDist(rng));

    //auto pos = *elementId;
    //infectedAvailablePositions.erase(elementId);

    std::size_t randomIndex = idDist(rng);
    auto pos = infectedAvailablePositions[randomIndex];
    infectedAvailablePositions.erase(infectedAvailablePositions.begin() + randomIndex);

    return pos;
}

std::pair<int16_t, int16_t> RespawnController::getObstacleRespawnPosition() {
    std::random_device dev;
    std::mt19937_64 rng(dev());

    std::uniform_int_distribution<size_t> idDist(0, obstacleAvailablePositions.size() - 1);
    auto elementId = obstacleAvailablePositions.begin();
    std::advance(elementId, idDist(rng));

    auto pos = *elementId;
    obstacleAvailablePositions.erase(elementId);

    return pos;
}

void RespawnController::resetRespawns() {
    this->createInfectedRespawns();
    this->createPlayerRespawns();
    this->createObstacleRespawns();
}

void RespawnController::createPlayerRespawns() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH / 2)  - (SIZE_SPRITE_X) + (SIZE_SPRITE_X * i),
                                                    (MAP_HEIGTH * 0.78) + ((SIZE_SPRITE_Y / 2.0) * j)};
            playerAvailablePositions.push_back(position);
        }
    }
}

void RespawnController::createInfectedRespawns() {
    // LEFT SIDE OF THE SCREEN
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 3; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH / 32.0) + ((SIZE_SPRITE_X / 2.0) * i),
                                                    (MAP_HEIGTH * 0.78) + ((SIZE_SPRITE_Y / 2.0) * j)};
            infectedAvailablePositions.push_back(position);
        }
    }

    // RIGHT SIDE OF THE SCREEN
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 3; j++ ) {
            std::pair<int16_t, int16_t> position = {((MAP_WIDTH * 3.0) / 4) + ((SIZE_SPRITE_X / 2.0) * i),
                                                    (MAP_HEIGTH * 0.78) + ((SIZE_SPRITE_Y / 2.0) * j)};
            infectedAvailablePositions.push_back(position);
        }
    }
}

void RespawnController::createObstacleRespawns() {
    // LEFT SIDE OF THE SCREEN
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH / 4) + ((SIZE_SPRITE_X) * i),
                                                    (MAP_HEIGTH * 0.8) + ((SIZE_SPRITE_Y / 2.0) * j)};
            obstacleAvailablePositions.push_back(position);
        }
    }

    // RIGHT SIDE OF THE SCREEN
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++ ) {
            std::pair<int16_t, int16_t> position = {(MAP_WIDTH * 3 / 5) + ((SIZE_SPRITE_X / 2) * i),
                                                    (MAP_HEIGTH * 0.8) + ((SIZE_SPRITE_Y / 2.0) * j)};
            obstacleAvailablePositions.push_back(position);
        }
    }
}
