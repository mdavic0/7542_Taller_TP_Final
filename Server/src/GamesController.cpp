#include "GamesController.h"
#include <string>

GamesController::GamesController() : counter(0), games(), mutex() {}

Queue<EventDTO*>* GamesController::create(EventDTO *eventdto,
                                          Queue<Snapshot *> *snapshot_queue,
                                          uint32_t &code) {
    std::string scenario = eventdto->getStr();
    std::lock_guard<std::mutex> locker(mutex);
    Game *newGame = new Game(counter, scenario);
    games.insert(std::pair{counter, newGame});
    code = counter++;
    return newGame->createGame(snapshot_queue, eventdto->getTypeOperator());
}

Queue<EventDTO*>* GamesController::try_join_game(EventDTO* eventdto,
                                                 Queue<Snapshot*> *snapshot_queue) {
    std::lock_guard<std::mutex> locker(mutex);
    uint32_t code = eventdto->getN();
    auto search = games.find(code);
    if (search != games.end()) {
        return search->second->joinGame(snapshot_queue, eventdto->getTypeOperator());
    }
    snapshot_queue->push(new Snapshot(Event::event_join, (uint8_t)0x01, 0));
    return nullptr;
}

void GamesController::startGame(const uint32_t& code){
    std::lock_guard<std::mutex> locker(mutex);
    auto search = games.find(code);
    if (search != games.end()) {
        return search->second->start();
    }

}

GamesController::~GamesController() {
  for (auto it = games.begin(); it != games.end(); ++it) {
    delete it->second;
  }
}
