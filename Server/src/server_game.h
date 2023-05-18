#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <vector>
#include <mutex>
#include <string>
#include "common_commanddto.h"
#include "common_responsedto.h"
#include "common_queue.h"

/*
 * TDA Game
 */
class Game {
    private:
        const uint32_t id;
        const std::string name;
        std::mutex mutex;
        std::vector<Queue<ResponseDTO*>*> queues;

    public:
        explicit Game(const uint32_t id, const std::string& name, Queue<ResponseDTO*> *q);

        /*
         * Este método debe añadir una nueva queue a la lista
         * de forma atomica
         */
        void join(Queue<ResponseDTO*> *q);

        /*
         * Este método debe pushear el meansaje que recibe
         * a todos los queues que contenga la sala de forma atomica
         */
        void broadcast(const std::string& msg);

        /*
         * No queremos permitir que alguien haga copias
         * */
         Game(const Game&) = delete;
         Game& operator=(const Game&) = delete;
};

#endif  // SERVER_GAME_H_
