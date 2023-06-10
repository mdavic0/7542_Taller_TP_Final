#include "GamesController.h"
#include <string>
#include <memory>

GamesController::GamesController() : counter(0), games(), mutex() {}

Queue<std::shared_ptr<EventDTO>>* GamesController::create(std::shared_ptr<EventDTO> eventdto,
                                                          Queue<std::shared_ptr<Snapshot>>* snapshot_queue,
                                                          uint32_t& code) {
    std::lock_guard<std::mutex> locker(mutex);
    Game *newGame = new Game(counter, eventdto->getStr(), eventdto->getTypeGame());
    games.insert(std::pair{counter, newGame});
    code = counter++;
    return newGame->createGame(snapshot_queue, eventdto->getTypeOperator());
}

Queue<std::shared_ptr<EventDTO>>* GamesController::try_join_game(std::shared_ptr<EventDTO> eventdto,
                                                 Queue<std::shared_ptr<Snapshot>> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    uint32_t code = eventdto->getN();
    auto search = games.find(code);
    if (search != games.end()) {
        return search->second->joinGame(q, eventdto->getTypeOperator());
    }
    q->push(std::make_shared<Snapshot>(Event::event_join, (uint8_t)0x01, 0));
    return nullptr;
}

void GamesController::startGame(const uint32_t& code){
    std::lock_guard<std::mutex> locker(mutex);
    auto search = games.find(code);
    if (search != games.end()) {
        return search->second->startGame();
    }

}

GamesController::~GamesController() {
  for (auto it = games.begin(); it != games.end(); ++it) {
    it->second->stop();
    delete it->second;
  }
}
