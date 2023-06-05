#ifndef GAMEDRAWNER_H
#define GAMEDRAWNER_H
#include "Thread.h"
#include "EventDTO.h"
#include "Queue.h"
#include "Snapshot.h"
#include <memory>

class GameDrawner : public Thread {
    private:
        Queue<std::shared_ptr<EventDTO>>& client_events;
        Queue<std::shared_ptr<Snapshot>>& snapshot_queue;
        bool& endGame;
        int menu;
    public:
        GameDrawner(Queue<std::shared_ptr<Snapshot>>& snapshot_queue,
            Queue<std::shared_ptr<EventDTO>>& client_events,
            bool& endGame, int menu);
        // implementar gameloop y cosas de SDL (eventos)
        virtual void run() override;
        virtual void stop() override;

};


#endif
