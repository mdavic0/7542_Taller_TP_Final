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
    bool& endGame, std::map<uint8_t, std::shared_ptr<Operator>>& soldiers,
    uint8_t idPlayer, uint8_t idMap, TypeGame mode, Font& font,
    std::map<uint8_t, std::shared_ptr<Enemy>>& enemies,
    std::map<uint8_t, std::shared_ptr<Obstacles>>& obstacles) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(endGame), events(eventQueue, idPlayer),
    map(idMap, this->renderer, this->window), soldiers(soldiers),
    hud(soldiers[idPlayer]->getType(), mode, renderer, font, window),
    idPlayer(idPlayer), mode(mode), font(font), enemies(enemies),
    camera(window), obstacles(obstacles) {
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
    std::shared_ptr<Snapshot> snap = nullptr;
    while (!snapshotQueue.try_pop(snap)) {
    }
    if (snap->getEvent() != Event::event_end) {
        for (auto &player : snap->getInfo()) {
            soldiers[player.getId()]->update(player.getPosition(),
                                                player.getState(),
                                                player.getHealth(),
                                                player.getMunition());
        }
        camera.update(calculateMassCenter());

        // Si no se actualizaron todos significa que alguno se desconecto
        if (soldiers.size() > snap->getInfo().size()) {
            for (auto &player : soldiers) {
                bool found = false;
                for (const auto& stOperator : snap->getInfo())
                    if (player.first == stOperator.getId()) {
                        found = true;
                        break;
                    }
                if (!found)
                    player.second->setState(State::dead);
            }
        }

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
    for (const auto& soldier : soldiers){
        massCenter.first += soldier.second->getPosX();
        massCenter.second += soldier.second->getPosY();
    }
    massCenter.first = massCenter.first / soldiers.size();
    massCenter.second = massCenter.second / soldiers.size();
    return massCenter;
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

