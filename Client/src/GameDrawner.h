#ifndef GAMEDRAWNER_H
#define GAMEDRAWNER_H
#include "Thread.h"
#include "EventDTO.h"
#include "Queue.h"
#include "Snapshot.h"
#include "RendererSdl.h"
#include "Font.h"
#include <memory>
#include <string>

class GameDrawner : public Thread {
    private:
        Queue<std::shared_ptr<EventDTO>>& client_events;
        Queue<std::shared_ptr<Snapshot>>& snapshot_queue;
        bool& endGame;
        int menu;
        void renderText(const std::string& text1, const std::string& text2,
                        Renderer& render, Font& font);
    public:
        GameDrawner(Queue<std::shared_ptr<Snapshot>>& snapshot_queue,
            Queue<std::shared_ptr<EventDTO>>& client_events,
            bool& endGame, int menu);
        // implementar gameloop y cosas de SDL (eventos)
        virtual void run() override;
        virtual void stop() override;

};


#endif
