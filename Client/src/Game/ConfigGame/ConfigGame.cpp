#include "ConfigGame.h"

ConfigGame::ConfigGame(std::shared_ptr<Snapshot> config, Renderer& render,
    WindowSdl& window) : textures(render, config->getMap()) {
    idMap = config->getMap();
    mode = config->getTypeGame();

    players.clear();
    for (auto &player : config->getInfo()) {
        players[player.getId()] = std::make_shared<Operator>(player.getId(), 
            player.getTypeOperator(), render);
    }

    enemies.clear();
    for (auto &infected : config->getEnemies()) {
        enemies[infected.getId()] = std::make_shared<Enemy>(textures, render,
                                    infected.getTypeInfected());
    }

    obstacles.clear();
    for (auto &obstacle : config->getObstacles()) {
        obstacles[obstacle.getId()] =
            std::make_shared<Obstacles>(obstacle.getTypeObstacle(), render,
                                        obstacle.getPosition(), textures);
    }
}

TextureManager& ConfigGame::getTextureManager() {
    return this->textures;
}

std::map<uint8_t, std::shared_ptr<Operator>>& ConfigGame::getPlayers() {
    return this->players;
}

std::map<uint8_t, std::shared_ptr<Enemy>>& ConfigGame::getEnemies() {
    return this->enemies;
}

std::map<uint8_t, std::shared_ptr<Obstacles>>& ConfigGame::getObstacles() {
    return this->obstacles;
}

TypeGame ConfigGame::getMode() {
    return this->mode;
}

ConfigGame::~ConfigGame() {
}
