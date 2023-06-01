#include "Game.h"
#include <string>

Game::Game(const uint32_t id, const std::string& name) :
    id(id), name(name), mutex(),
    unprocessed_events(1000), client_snapshot_queues(),
    talking(true), alive(true), gameWorld(), started(false) {}

void Game::run() {
    try {
        gameLoop();
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

Queue<EventDTO*>* Game::joinGame(Queue<Snapshot*> *q) {
    std::lock_guard<std::mutex> locker(mutex);
    client_snapshot_queues.push_back(q);
    return &this->unprocessed_events;
}

void Game::startPlaying() {
    started = true;
}

void Game::gameLoop() {
    using namespace std::chrono;
    while (alive) {
        auto begin = std::chrono::steady_clock::now();

        //process_events() // popea hasta que no haya más eventos en la queue
        // y los procesa en el gameworld.
        processEvents();

        if (not started) {
            continue;
        }

        // TODO:
        //  step(some_time)
        gameWorld.simulateStep();
        // simula un tiempito en el 'gameworld'.
        // Este tiempito lo que va a hacer es hacer que falte menos
        // para poder lanzar una grandada, que los jugadores se muevan,
        // todos los eventos que tienen que ver con el tiempo.

        Snapshot* snapshot = gameWorld.getSnapshot();
        // broadcastSnapshot() # acá recien se agarra el snapshot y se lo pushea
        // a los hilos sender. Un snapshot por gameloop. Si hacen uno por evento,
        // saturan la red sin sentido
        broadcastSnapshot(snapshot);

        // ->>Bueno y el sleep de tiempo variable también
        auto end = std::chrono::steady_clock::now();
        int t_delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        // duration<double>(t_delta)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 20 - t_delta));
    }
}

void Game::processEvents() {
    EventDTO *event = nullptr;
    int iterations = 0;
    try {
        // try_pop es no bloqueante y devuelve false en caso de que la queue este vacia
        while (unprocessed_events.try_pop(event) && iterations < 10) {
            if (event->getEvent() == Event::event_create) {
                gameWorld.addPlayer(event->getTypeOperator());
                broadcastSnapshot(new Snapshot(Event::event_create, id));
                break;
            } else if (event->getEvent() == Event::event_join) {
                gameWorld.addPlayer(event->getTypeOperator());
                broadcastSnapshot(new Snapshot(Event::event_join, (uint8_t)0x01));
                break;
            } else if (event->getEvent() == Event::event_start_game) {
                std::cout << "Empieza el juego!\n";
                startPlaying();
                break;
            } else if (event->getEvent() == Event::event_move
                    || event->getEvent() == Event::event_stop_move) {
                std::cout << "Popeo un evento de movimiento\n";
                gameWorld.updateMovementDirection(event->getEvent(),
                                                  event->getTypeOperator(),
                                                  event->getMoveTo());
            }
            iterations++;
        }
    } catch(ClosedQueue& e) {
            // hacer algo
    }
}

void Game::broadcastSnapshot(Snapshot* snapshot) {
    std::lock_guard<std::mutex> l(mutex);
    for (auto const& i : this->client_snapshot_queues) {
        // TODO: usar shared pointer para el snapshot (ya que sino el
        //      sender de cada SVclient va a hacer pop del snapshot y
        //      despues delete, dejandolo null para los demas SVclients).
        i->push(snapshot);
    }
}

Game::~Game() {
    join();
}