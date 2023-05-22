#include "server_games_controller.h"
#include <string>

GamesController::GamesController() : counter(0), games(), mutex() {}

uint32_t GamesController::create(EventDTO *eventdto, Queue<Snapshot *>* snapshot_queue) {
    std::string scenario = eventdto->getStr();
    std::lock_guard<std::mutex> locker(mutex);
    Game *newGame = new Game(counter, scenario, snapshot_queue);
    games.insert(std::pair{counter, newGame});
    newGame->start();
    return counter++;
}

uint8_t GamesController::try_join_game(EventDTO* eventdto, Queue<Snapshot*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    uint32_t code = eventdto->getN();
    auto search = games.find(code);
    if (search != games.end()) {
        search->second->join_game(q);
        return 0x00;    // join client to game
    }
    return 0x01;
}

Queue<EventDTO*>* GamesController::get_event_queue(uint32_t code) {
    return games.at(code)->get_event_queue();
}

GamesController::~GamesController() {
  for (auto it = games.begin(); it != games.end(); ++it) {
    delete it->second;
  }
}
