#include "Game.h"
#include <memory>
#include <string>
#include <random>
#include <functional>
#include <iterator>
#include <utility>

Game::Game(const uint32_t id, std::string name, const TypeGame& type, const TypeDifficulty& difficulty,
    StatsController& statsController) : id(id), name(std::move(name)), mutex(),
    unprocessed_events(QUEUE_MAX_SIZE), client_snapshot_queues(),
    talking(true), alive(true), gameWorld(type, difficulty),
    started(false), commandFactory(), statsController(statsController), sendStats(false) {}

void Game::run() {
    try {
        auto startGameTime = std::chrono::steady_clock::now();

        while(talking && client_snapshot_queues.size() > 0) {
            gameLoop();
        }

        if (sendStats) {
            auto endGameTime = std::chrono::steady_clock::now();
            auto duration = endGameTime - startGameTime;

            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - minutes);

            uint16_t minutesValue = static_cast<uint16_t>(minutes.count());
            uint16_t secondsValue = static_cast<uint16_t>(seconds.count());

            std::vector<StatsDto> stats = gameWorld.getStats();
            if (!stats.empty())
                broadcastSnapshot(statsController.updateStats(stats, minutesValue, secondsValue));

            closeAllQueue();
        }

    } catch (const std::exception& exc) {
        std::cout << "Game - Exception occurred test log: " << exc.what() << std::endl;
    }
    alive = false;
}

void Game::stop() {
    talking = false;
    std::cout << "Game - stop " << std::endl;
}

bool Game::ended() {
    return !alive;
}

bool Game::running() {
    return started && alive;
}

Queue<std::shared_ptr<EventDTO>>* Game::createGame(Queue<std::shared_ptr<Snapshot>> *q,
                                                   const TypeOperator& op) {
    uint16_t idPlayer = gameWorld.addPlayer(op);
    client_snapshot_queues.insert({idPlayer, q});
    q->push(std::make_shared<Snapshot> (Event::event_create, id, idPlayer));
    return &this->unprocessed_events;
}

Queue<std::shared_ptr<EventDTO>>* Game::joinGame(Queue<std::shared_ptr<Snapshot>> *q,
                                                 const TypeOperator& op) {
    if (not started) {                 
        uint16_t idPlayer = gameWorld.addPlayer(op);
        client_snapshot_queues.insert({idPlayer, q});
        // Notify all clients that a new player joined
        for (auto &clientQueue : client_snapshot_queues) {
            clientQueue.second->push(std::make_shared<Snapshot>(Event::event_join,
                                                        JOIN_OK,
                                                        idPlayer, client_snapshot_queues.size()));
        }
        
        return &this->unprocessed_events;
    }
    // JOIN FAILED
    q->push(std::make_shared<Snapshot>(Event::event_join, JOIN_FAILED, 0, 0));
    return nullptr;
}

void Game::startGame() {
    if (not started) {
        this->started = true;
        std::shared_ptr<Snapshot> snapshot = gameWorld.getSnapshot(true);
        broadcastSnapshot(snapshot);
        this->start();
    }
}

void Game::clientLeave(Queue<std::shared_ptr<Snapshot>> *q) {
   std::lock_guard<std::mutex> locker(mutex);
    if (not started) {
        for (auto it = client_snapshot_queues.begin(); it != client_snapshot_queues.end(); ) {
            if (it->second == q) {
                q->close();
                it = client_snapshot_queues.erase(it);
            } else {
                ++it;
            }
        }
    }
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
            sendStats = true;
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
        try {
            if (!it->second->try_push(snapshot)) {
                gameWorld.deletePlayer(it->first);
                it->second->close();
                it = client_snapshot_queues.erase(it);
            } else {
                ++it;
            }
        } catch(ClosedQueue& e) {
            gameWorld.deletePlayer(it->first);
            it = client_snapshot_queues.erase(it);
        }
    }
}

void Game::closeAllQueue() {
    for (auto it = client_snapshot_queues.begin(); it != client_snapshot_queues.end(); it++) {
        try {
            it->second->close();
        } catch(ClosedQueue& e) {
            //
        }
    }
}

Game::~Game() {
    if (started)
        join();
    std::cout << "Game - end delete " << std::endl;
}
