#include "server_game.h"
#include <string>

Game::Game(const uint32_t id, const std::string& name, Queue<Snapshot*> *q) :
    id(id), name(name.c_str()), mutex(), queues() {
    queues.push_back(q);
    }

void Game::join(Queue<Snapshot*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    queues.push_back(q);
}

void Game::broadcast(const std::string& msg) {
    std::lock_guard<std::mutex> locker(mutex);
    for (long unsigned int i = 0; i < queues.size(); i++) {
        Snapshot *response = new Snapshot(Event::event_broadcast, 0, 0, msg);
        queues[i]->push(response);
    }
}
