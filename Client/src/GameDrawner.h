#ifndef GAMEDRAWNER_H
#define GAMEDRAWNER_H
#include "common_thread.h"
#include "common_eventdto.h"
#include "common_queue.h"
#include "common_snapshot.h"

class GameDrawner : public Thread {
    private:
        Queue<EventDTO*>& client_events;
        Queue<Snapshot*>& snapshot_queue;
        bool& endGame;
    public:
        GameDrawner(Queue<EventDTO*>& client_events,
            Queue<Snapshot*>& snapshot_queue, bool& endGame);
        // implementar gameloop y cosas de SDL (eventos)
        virtual void run() override;
        virtual void stop() override;

};


#endif
