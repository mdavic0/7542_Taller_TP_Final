#include "Game.h"
#include <memory>
#include <string>
#include <random>
#include <functional>
#include <iterator>
#include <utility>

Game::Game(const uint32_t id, std::string name, const TypeGame& type) :
    id(id), name(std::move(name)), mutex(),
    unprocessed_events(1000), client_snapshot_queues(),
    talking(true), alive(true), gameWorld(type),
    started(false), commandFactory() {}

void Game::run() {
    try {
        while(talking) {
            gameLoop();
        }
    } catch (const std::exception& exc) {
        std::cout << "Game - Exception occurred test log: " << exc.what() << std::endl;
    }
    alive = false;
}

void Game::stop() {
    std::cout << "Game - stop " << std::endl;
    talking = false;
    std::cout << "Game - end stop " << std::endl;
}

bool Game::ended() {
    return !alive;
}

Queue<std::shared_ptr<EventDTO>>* Game::createGame(Queue<std::shared_ptr<Snapshot>> *q,
                                                   const TypeOperator& op) {
    uint8_t idPlayer = gameWorld.addPlayer(op);
    client_snapshot_queues.insert({idPlayer, q});
    q->push(std::make_shared<Snapshot> (Event::event_create, id, idPlayer));
    return &this->unprocessed_events;
}

Queue<std::shared_ptr<EventDTO>>* Game::joinGame(Queue<std::shared_ptr<Snapshot>> *q,
                                                 const TypeOperator& op) {
    if (not started) {                   
        std::lock_guard<std::mutex> locker(mutex);
        uint8_t idPlayer = gameWorld.addPlayer(op);
        client_snapshot_queues.insert({idPlayer, q});
        // Notify all clients that a new player joined
        for (auto &clientQueue : client_snapshot_queues) {
            clientQueue.second->push(std::make_shared<Snapshot>(Event::event_join,
                                                        (uint8_t)0x00,
                                                        idPlayer, client_snapshot_queues.size()));
        }
        
        return &this->unprocessed_events;
    }
    // JOIN FAILED
    q->push(std::make_shared<Snapshot>(Event::event_join, (uint8_t)0x01, 0, 0));
    return nullptr;
}

void Game::startGame() {
    this->started = true;
    std::shared_ptr<Snapshot> snapshot = gameWorld.getSnapshot(true);
    broadcastSnapshot(snapshot);
    this->start();
} 

void Game::gameLoop() {
    using namespace std::chrono;
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    double t_delta;
    int skippedLoops = 0;

    while (talking && client_snapshot_queues.size() > 0) {
        begin = steady_clock::now();

        processEvents();

        gameWorld.simulateStep(STEP_TIME * (skippedLoops + 1));

        std::shared_ptr<Snapshot> snapshot = gameWorld.getSnapshot(false);
        broadcastSnapshot(snapshot);

        end = steady_clock::now();
        t_delta = duration<double>(end - begin).count();

        if (t_delta < STEP_TIME) {
            std::this_thread::sleep_for(duration<double>(STEP_TIME - t_delta));
        }

        if(gameWorld.isEnded()){
            broadcastSnapshot(gameWorld.getStats());
            stop();
        }
    }
}

void Game::processEvents() {
    std::shared_ptr<EventDTO> event = nullptr;
    int iterations = 0;
    try {
        // try_pop es no bloqueante y devuelve false en caso de que la queue este vacia
        while (unprocessed_events.try_pop(event) && iterations < MAX_ITERATIONS) {
            std::unique_ptr<Command> command = commandFactory.getCommand(event);
            command->execute(this->gameWorld);

            if (event->getEvent() == Event::event_leave) {
                std::lock_guard<std::mutex> locker(mutex);

                auto search = client_snapshot_queues.find(event->getIdPlayer());
                if (search != client_snapshot_queues.end()) {
                    search->second->close();
                    client_snapshot_queues.erase(search);
                }
            }

            iterations++;
        }
    } catch(ClosedQueue& e) {
            // hacer algo
    }
}

void Game::broadcastSnapshot(std::shared_ptr<Snapshot> snapshot) {
    std::lock_guard<std::mutex> locker(mutex);
    for (auto it = client_snapshot_queues.begin(); it != client_snapshot_queues.end(); /* increment inside loop */) {
        if (!it->second->try_push(snapshot)) {
            std::cout << "Push failed, need to remove client " << it->first << std::endl;
            gameWorld.deletePlayer(it->first);
            it->second->close();
            it = client_snapshot_queues.erase(it);
        } else {
            ++it;
        }
    }
}

Game::~Game() {
    if (started)
        join();
    std::cout << "Game - end delete " << std::endl;
}