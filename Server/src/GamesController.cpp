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
    // newGame->start(); TODO: QUE LO HAGA EL GAME CUANDO LLEGAN N JUGADORES (INTERNAMENTE) /
    //                      O CUANDO LLEGA UN START_GAME DEL LADO DEL CLIENT
    return newGame->joinGame(snapshot_queue);
}

Queue<EventDTO*>* GamesController::try_join_game(EventDTO* eventdto,
                                                 Queue<Snapshot*> *q,
                                                 uint8_t& ok) {
    std::lock_guard<std::mutex> locker(mutex);
    uint32_t code = eventdto->getN();
    auto search = games.find(code);
    if (search != games.end()) {
        ok = 0x00;    // join client to game
        return search->second->joinGame(q);
    }
    ok = 0x01;
    return nullptr;
}

GamesController::~GamesController() {
  for (auto it = games.begin(); it != games.end(); ++it) {
    delete it->second;
  }
}
