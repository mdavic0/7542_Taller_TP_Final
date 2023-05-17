#include "server_games_controller.h"
#include <string>

GamesController::GamesController() : counter(0), games(), mutex() {}

uint32_t GamesController::create(const CommandDTO& commanddto, Queue<ResponseDTO*> *q) {
    std::string scenario = commanddto.getStr();
    std::lock_guard<std::mutex> locker(mutex);
    Game *newGame = new Game(counter, scenario, q);
    games.insert(std::pair{counter, newGame});
    return counter++;
}

uint8_t GamesController::join(const CommandDTO& commanddto, Queue<ResponseDTO*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    uint32_t code = commanddto.getN();
    auto search = games.find(code);
    if (search != games.end()) {
        search->second->join(q);
        return 0x00;    // join client to game
    }
    return 0x01;
}

void GamesController::broadcast(uint32_t game, const CommandDTO& commanddto) {
    std::lock_guard<std::mutex> locker(mutex);
    std::string msg = commanddto.getStr();
    auto search = games.find(game);
    if (search != games.end()) {
        search->second->broadcast(msg);
        return;
    }
}

GamesController::~GamesController() {
  for (auto it = games.begin(); it != games.end(); ++it) {
    delete it->second;
  }
}
