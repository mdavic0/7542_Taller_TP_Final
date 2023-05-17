#include "server_game.h"
#include <string>

Game::Game(const uint32_t id, const std::string& name, Queue<ResponseDTO*> *q) :
    id(id), name(name.c_str()), mutex(), queues() {
    queues.push_back(q);
    }

void Game::join(Queue<ResponseDTO*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    queues.push_back(q);
}

void Game::broadcast(const std::string& msg) {
    std::lock_guard<std::mutex> locker(mutex);
    for (long unsigned int i = 0; i < queues.size(); i++) {
        ResponseDTO *response = new ResponseDTO(Command::command_broadcast, 0, 0, msg);
        queues[i]->push(response);
    }
}
