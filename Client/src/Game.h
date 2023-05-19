#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H
#include "common_thread.h"
#include "common_eventdto.h"
#include "common_queue.h"
#include "common_snapshot.h"

class Game {
    Queue<EventDTO*>& client_events;
    Queue<Snapshot*>& snapshot_queue;

    public:
        Game(Queue<EventDTO*>& client_events, Queue<Snapshot*>& snapshot_queue);
        // implementar gameloop y cosas de SDL (eventos)
        void run();
};


#endif //LEFT4DEAD_GAME_H
