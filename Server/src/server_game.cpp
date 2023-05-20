#include "server_game.h"
#include <string>

Game::Game(const uint32_t id, const std::string& name, Queue<Snapshot*> *q) :
    id(id), name(name), mutex(),
    unprocessed_events(1000), client_snapshot_queues(),
    talking(true), alive(true) {
    client_snapshot_queues.push_back(q);
    }

Queue<EventDTO *> *Game::get_event_queue() {
    return &this->unprocessed_events;
}

void Game::run() {
    try {
        //game_loop();
    } catch(std::exception& e) {

    }
    alive = false;
}

void Game::stop() {
    //talking = false;
}

bool Game::ended() {
    return !alive;
}

void Game::join(Queue<Snapshot*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    client_snapshot_queues.push_back(q);
}

void Game::game_loop() {
    while (alive) {
        //process_events() // popea hasta que no haya más eventos en la queue
        // y los procesa en el gameworld.
        //step(some_time) //# simula un tiempito en el mundo del juego.
        // Este tiempito lo que va a hacer es hacer que falte menos
        // para poder lanzar una grandada, que los jugadores se muevan,
        // todos los eventos que tienen que ver con el tiempo.
        // broadcast_snapshot() # acá recien se agarra el snapshot y se lo pushea
        // a los hilos sender. Un snapshot por gameloop. Si hacen uno por evento,
        // saturan la red sin sentido
        // ->>Bueno y el sleep de tiempo variable también
    }
}

