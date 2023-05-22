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
        game_loop();
    } catch(std::exception& e) {
        // hacer algo
    }
    alive = false;
}

void Game::stop() {
    talking = false;
}

bool Game::ended() {
    return !alive;
}

void Game::join_game(Queue<Snapshot*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    client_snapshot_queues.push_back(q);
}

void Game::game_loop() {
    using namespace std::chrono;
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    double t_delta;

    while (alive) {
        begin = steady_clock::now();
        //process_events() // popea hasta que no haya más eventos en la queue
        // y los procesa en el gameworld.
        // TODO: crear ese 'gameworld' que va a tener el estado actual de cada
        //      player (position, typeoperator, vida, veces caido, etc...)
        Snapshot* snapshot = process_events();
        if (!snapshot) {
            continue;
        }
        // TODO:
        //  step(some_time) //# simula un tiempito en el 'gameworld'.
        // Este tiempito lo que va a hacer es hacer que falte menos
        // para poder lanzar una grandada, que los jugadores se muevan,
        // todos los eventos que tienen que ver con el tiempo.

        // broadcast_snapshot() # acá recien se agarra el snapshot y se lo pushea
        // a los hilos sender. Un snapshot por gameloop. Si hacen uno por evento,
        // saturan la red sin sentido
        broadcast_snapshot(snapshot);

        // ->>Bueno y el sleep de tiempo variable también
        end = steady_clock::now();
        t_delta = duration<double>(end - begin).count();
        std::this_thread::sleep_for(duration<double>(t_delta));
    }
}

// De momento hago que popee hasta que no haya más eventos en la queue
// y cree el snapshot y lo devuelva
Snapshot* Game::process_events() {
    EventDTO *event = nullptr;
    Snapshot* snapshot = nullptr;
    try {
        // try_pop es no bloqueante y devuelve false en caso de que la queue este vacia
        while (unprocessed_events.try_pop(event)) {
            if (event->getEvent() == Event::event_create) {
                snapshot = new Snapshot(Event::event_create,
                                        event->getTypeOperator(),
                                        event->getN(),
                                        0, 0, 0);
                break;
            } else if (event->getEvent() == Event::event_join) {
                snapshot = new Snapshot(Event::event_join,
                                        event->getTypeOperator(),
                                        event->getN(),
                                        0, 0, 0);
                break;
            } else if (event->getEvent() == Event::event_move) {
                // TODO: actualizo la position del player y creo el snapshot.
                //       En realidad en este caso no se va a crear el snapshot de una
                //       sino que se va a actualizar el 'gameworld' y una vez
                //       que no haya mas events por procesar se crea el snapshot
                snapshot = new Snapshot(Event::event_move,
                                        event->getTypeOperator(),
                                        event->getN(),
                                        0, 0, 0);
            }
            // delete event;
        }
    } catch(ClosedQueue& e) {
            // hacer algo
    }
    return snapshot;
}

void Game::broadcast_snapshot(Snapshot* snapshot) {
    std::lock_guard<std::mutex> l(mutex);
    for (auto const& i : this->client_snapshot_queues) {
        // TODO: usar shared pointer para el snapshot (ya que sino el
        //      sender de cada SVclient va a hacer pop del snapshot y
        //      despues delete, dejandolo null para los demas SVclients).
        i->push(snapshot);
    }
}

