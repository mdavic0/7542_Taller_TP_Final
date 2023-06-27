#ifndef GAMEDRAWNER_H
#define GAMEDRAWNER_H
#include "Thread.h"
#include "EventDTO.h"
#include "Queue.h"
#include "Snapshot.h"
#include "RendererSdl.h"
#include "WindowSdl.h"
#include "Font.h"
#include <memory>
#include <string>

class GameDrawner : public Thread {
    private:
        Queue<std::shared_ptr<EventDTO>>& client_events;
        Queue<std::shared_ptr<Snapshot>>& snapshot_queue;
        bool& error;
        int menu;
        int numPlayers;
        int16_t idPlayer;
        bool gameEnded;
    
    public:
        GameDrawner(Queue<std::shared_ptr<Snapshot>>& snapshot_queue,
            Queue<std::shared_ptr<EventDTO>>& client_events,
            bool& error, int menu, uint16_t idPlayer, uint8_t numPlayers);
        virtual ~GameDrawner();
        virtual void run() override;
        virtual void stop() override;

};


#endif
