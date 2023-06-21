#include "GameSdl.h"
#include "Defines.h"
#include "Operator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    bool& endGame, uint8_t idPlayer, Font& font, ConfigGame& config) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(endGame), events(eventQueue, idPlayer),
    map(config.getIdMap(), this->renderer, this->window),
    soldiers(config.getPlayers()),
    hud(soldiers[idPlayer]->getType(), config.getMode(), renderer, font, window),
    idPlayer(idPlayer), mode(config.getMode()), font(font),
    enemies(config.getEnemies()), camera(window), obstacles(config.getObstacles()) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

void GameSdl::render() {
    this->map.render(camera.getRect());
    
    for (const auto &obstacle: obstacles)
        obstacle.second->render(camera.getRect());

    this->hud.render(soldiers[idPlayer]->getHealth(),
                    soldiers[idPlayer]->getMunition(),
                    enemies.size());
    
    // reordeno los enemigos antes de renderizar
    std::vector<std::pair<uint8_t,std::shared_ptr<Enemy>>> vecEnemies(
        enemies.begin(), enemies.end());
    std::sort(vecEnemies.begin(), vecEnemies.end(),
        [](const auto& a, const auto&b) {
            return a.second->getPosY() < b.second->getPosY();
    });
    for (const auto &enemy : vecEnemies)
        enemy.second->render(camera.getRect());
    
    // reordeno los operadores antes de renderizar
    std::vector<std::pair<uint8_t,std::shared_ptr<Operator>>> vecSoldiers(
        soldiers.begin(), soldiers.end());
    std::sort(vecSoldiers.begin(), vecSoldiers.end(), 
        [](const auto& a, const auto&b) {
            return a.second->getPosY() < b.second->getPosY();
    });
    for (const auto &soldier : vecSoldiers)
        soldier.second->render(camera.getRect());
}

void GameSdl::update() {
    std::shared_ptr<Snapshot> snap = snapshotQueue.pop();
    if (snap->getEvent() != Event::event_end) {
        // for (auto &player : snap->getInfo()) {
        // }

        // Actualizo todos los clientes si no actualizo a uno significa
        // que alguno se desconecto
        if (soldiers.size() >= snap->getInfo().size()) {
            for (auto &player : soldiers) {
                bool found = false;
                for (const auto& stOperator : snap->getInfo())
                    if (player.first == stOperator.getId()) {
                        player.second->update(stOperator.getPosition(),
                                                stOperator.getState(),
                                                stOperator.getHealth(),
                                                stOperator.getMunition());
                        found = true;
                        break;
                    }
                if (!found)
                    player.second->setState(State::dead);
            }
        }
        camera.update(calculateMassCenter());

        std::unordered_set<uint8_t> mapIds;
        for (auto &infected : snap->getEnemies()) {
            mapIds.insert(infected.getId());
            enemies[infected.getId()]->update(infected.getPosition(),
                                                infected.getState());
        }

        // Eliminio enemigo muerto
        auto iterator = enemies.begin();
        while (iterator != enemies.end()) {
            if (mapIds.find(iterator->first) == mapIds.end())
                iterator = enemies.erase(iterator);
            else
                ++iterator;
        }
    } else {
        this->endGame = true;
    }
}

std::pair<int16_t, int16_t> GameSdl::calculateMassCenter() {
    std::pair<int16_t, int16_t> massCenter;
    size_t soldiersLive = 0;
    for (const auto& soldier : soldiers) {
        if (soldier.second->getState() != State::dead) {
            massCenter.first += soldier.second->getPosX();
            massCenter.second += soldier.second->getPosY();
            soldiersLive++;
        }
    }
    massCenter.first = massCenter.first / soldiersLive;
    massCenter.second = massCenter.second / soldiersLive;
    return massCenter;
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

