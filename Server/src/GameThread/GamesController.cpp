#include "GamesController.h"
#include <string>
#include <memory>
#include <iostream>
#include <random>

GamesController::GamesController() : games(), mutex(), statsController(STATS_PATH) {}

Queue<std::shared_ptr<EventDTO>>* GamesController::create(std::shared_ptr<EventDTO> eventdto,
                                                          Queue<std::shared_ptr<Snapshot>>* snapshot_queue,
                                                          std::shared_ptr<Game>& game) {
    std::lock_guard<std::mutex> locker(mutex);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<uint32_t> distribution(0, sizeof(uint32_t));

    uint32_t key = distribution(generator);
    while (games.count(key) > 0) {
        key = distribution(generator);
    }
    std::shared_ptr<Game> newGame = std::make_shared<Game>(key, eventdto->getStr(), eventdto->getTypeGame(),
        eventdto->getTypeDifficulty(), statsController);
    games.insert(std::pair{key, newGame});
    game = newGame;
    return newGame->createGame(snapshot_queue, eventdto->getTypeOperator());
}

Queue<std::shared_ptr<EventDTO>>* GamesController::try_join_game(std::shared_ptr<EventDTO> eventdto,
                                                 Queue<std::shared_ptr<Snapshot>>* q,
                                                 std::shared_ptr<Game>& game) {
    std::lock_guard<std::mutex> locker(mutex);
    uint32_t code = eventdto->getN();
    auto search = games.find(code);
    if (search != games.end()) {
        game = search->second;
        return search->second->joinGame(q, eventdto->getTypeOperator());
    }
    q->push(std::make_shared<Snapshot>(Event::event_join, JOIN_FAILED, 0, 0));
    return nullptr;
}

GamesController::~GamesController() {
    for (auto it = games.begin(); it != games.end(); ++it) {
        it->second->stop();
    }
}
