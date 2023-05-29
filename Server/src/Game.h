#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <list>
#include <mutex>
#include <string>
#include "EventDTO.h"
#include "Snapshot.h"
#include "Queue.h"
#include "Thread.h"
#include "GameWorld.h"
#include <atomic>

/*
 * TDA Game
 */
class Game : public Thread {
    private:
        const uint32_t id;
        const std::string name;
        std::mutex mutex;
        Queue<EventDTO*> unprocessed_events;
        std::list<Queue<Snapshot*>*> client_snapshot_queues;
        std::atomic<bool> talking;
        std::atomic<bool> alive;
        GameWorld gameWorld;
        bool started;
    public:
        explicit Game(const uint32_t id, const std::string& name);

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
         * de forma atomica
         */
        Queue<EventDTO*>* joinGame(Queue<Snapshot*> *q);

        void startPlaying();
        /*
         * No queremos permitir que alguien haga copias
         * */
         Game(const Game&) = delete;
         Game& operator=(const Game&) = delete;
         ~Game();

    private:
        void gameLoop();
        void processEvents();
        void broadcastSnapshot(Snapshot* snapshot);
};

#endif  // SERVER_GAME_H_
