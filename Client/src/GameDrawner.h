#ifndef GAMEDRAWNER_H
#define GAMEDRAWNER_H
#include "Thread.h"
#include "EventDTO.h"
#include "Queue.h"
#include "Snapshot.h"

class GameDrawner : public Thread {
    private:
        Queue<EventDTO*>& client_events;
        Queue<Snapshot*>& snapshot_queue;
        bool& endGame;
    public:
        GameDrawner(Queue<Snapshot*>& snapshot_queue,
            Queue<EventDTO*>& client_events, bool& endGame);
        // implementar gameloop y cosas de SDL (eventos)
        virtual void run() override;
        virtual void stop() override;

};


#endif
