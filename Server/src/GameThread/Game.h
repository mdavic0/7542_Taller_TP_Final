#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <list>
#include <mutex>
#include <string>
#include <atomic>
#include <memory>
#include "EventDTO.h"
#include "Snapshot.h"
#include "Queue.h"
#include "Thread.h"
#include "GameWorld.h"
#include "Command.h"
#include "CommandFactory.h"
#include "StatsController.h"

/*
 * TDA Game
 */
class Game : public Thread {
    private:
    const uint32_t id;
        const std::string name;
        std::mutex mutex;
        Queue<std::shared_ptr<EventDTO>> unprocessed_events;
        std::map<uint16_t, Queue<std::shared_ptr<Snapshot>>*> client_snapshot_queues;
        std::atomic<bool> talking;
        std::atomic<bool> alive;
        std::atomic<bool> started;
        std::atomic<bool> sendStats;
        GameWorld gameWorld;
        CommandFactory commandFactory;
        StatsController& statsController;

    public:
        Game(const uint32_t id, std::string  name, const TypeGame& type,
                const TypeDifficulty& difficulty, StatsController& statsController);

        virtual void run() override;

        /*
        * Método para detener la ejecución el hilo.
        */
        virtual void stop() override;

        /*
        * Método que devuelve true cuando el hilo termino de ejecutarse.
        */
        bool ended();

        /*
         * Este método debe añadir una nueva queue a la lista
         * de forma atomica y pushear el snapshot de create
         */
        Queue<std::shared_ptr<EventDTO>> *
        createGame(Queue<std::shared_ptr<Snapshot>> *q, const TypeOperator &op);

        /*
         * Este método debe añadir una nueva queue a la lista
         * de forma atomica y pushear el snapshot de join
         */
        Queue<std::shared_ptr<EventDTO>>* joinGame(Queue<std::shared_ptr<Snapshot>> *q, const TypeOperator& op);

        /*
         * Este método setea a true el atributo started que sirve para
         * que posteriormente no se puedan unir clientes una vez que comenzo
         * el juego, a su vez hace el start del hilo.
         */
        void startGame();

        void clientLeave(Queue<std::shared_ptr<Snapshot>> *q);

        bool running();

        /*
         * No queremos permitir que alguien haga copias
         * */
         Game(const Game&) = delete;
         Game& operator=(const Game&) = delete;
         ~Game();

private:
        void gameLoop();

        /*
         * Popea hasta que no haya más eventos en la queue
         * y los procesa en el GameWorld.
         */
        void processEvents();

        /*
         * Pushea el Snapshot a los hilos sender.
         * Un snapshot por gameloop
         */
        void broadcastSnapshot(std::shared_ptr<Snapshot> snapshot);
};

#endif  // SERVER_GAME_H_
