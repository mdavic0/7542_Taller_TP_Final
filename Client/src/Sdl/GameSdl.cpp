#include "GameSdl.h"
#include "Defines.h"
#include <iostream>
#include <vector>
#include <algorithm>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    bool& endGame, std::map<uint8_t, std::shared_ptr<Operator>>& soldiers,
    uint8_t idPlayer, uint8_t idMap, TypeGame mode, Font& font,
    std::map<uint8_t, std::shared_ptr<Enemy>>& enemys) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(endGame), events(eventQueue, idPlayer),
    map(3, this->renderer), soldiers(soldiers),
    hud(soldiers[idPlayer]->getType(), renderer, font),
    idPlayer(idPlayer), mode(mode), font(font), enemys(enemys) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

/*
Para renderizar correctamente lo player se necesita ordenar por la posicion y
*/ 
bool comparePosition(const std::pair<uint8_t, std::shared_ptr<Operator>>& a,
                    const std::pair<uint8_t, std::shared_ptr<Operator>>& b) {
    return a.second->getPosY() < b.second->getPosY();
}

void GameSdl::render() {
    this->map.render();
    this->hud.render(soldiers[idPlayer]->getHealth(), 0);
    std::vector<std::pair<uint8_t, std::shared_ptr<Operator>>> vec(
        soldiers.begin(), soldiers.end());
    std::sort(vec.begin(), vec.end(), comparePosition);
    for (const auto &soldier : vec)
        soldier.second->render();
    for (const auto &enemy : enemys)
        enemy.second->render();
}

void GameSdl::update() {
    std::shared_ptr<Snapshot> snap = snapshotQueue.pop();
    std::map<uint8_t, StOperator> players = snap->getInfo();
    for (auto &player : players)
        soldiers[player.second.getId()]->update(player.second.getPosition(),
                                                player.second.getState(),
                                                player.second.getHealth());
    for (size_t i = 0; i < enemys.size(); i++)
        enemys[(uint8_t)i]->update({600, 500 + i*10}, State::idle, 100);
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

