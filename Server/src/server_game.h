#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <list>
#include <mutex>
#include <string>
#include "common_eventdto.h"
#include "common_snapshot.h"
#include "common_queue.h"
#include "common_thread.h"
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
    public:
        explicit Game(const uint32_t id, const std::string& name, Queue<Snapshot*>* snapshot_queue);

        Queue<EventDTO*>* get_event_queue();

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
        void join_game(Queue<Snapshot*> *q);

        /*
         * No queremos permitir que alguien haga copias
         * */
         Game(const Game&) = delete;
         Game& operator=(const Game&) = delete;

    private:
        void game_loop();
        Snapshot* process_events();
        void broadcast_snapshot(Snapshot* snapshot);
};

#endif  // SERVER_GAME_H_
