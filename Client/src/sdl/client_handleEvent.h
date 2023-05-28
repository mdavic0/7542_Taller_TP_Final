#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include "common_move.h"
#include "common_queue.h"
#include "common_eventdto.h"

class EventHandler {
    private:
        MoveTo moveDirection;
        bool running;
        Queue<EventDTO*>& eventQueue;
        void handleKeyDownEvent(SDL_Keysym keysym);
        void handleKeyUpEvent(SDL_Keysym keysym);
    public:
        EventHandler(Queue<EventDTO*>& eventQueue);
        ~EventHandler();
        MoveTo getMoveDirection() const;
        bool isRunning();
        void listen();
};

#endif
