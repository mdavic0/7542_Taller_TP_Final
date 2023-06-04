#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include "Move.h"
#include "Queue.h"
#include "EventDTO.h"
#include <memory>

class EventHandler {
    private:
        MoveTo moveDirection;
        bool running;
        Queue<std::shared_ptr<EventDTO>>& eventQueue;
        void handleKeyDownEvent(SDL_Keysym keysym);
        void handleKeyUpEvent(SDL_Keysym keysym);
    public:
        EventHandler(Queue<std::shared_ptr<EventDTO>>& eventQueue);
        ~EventHandler();
        MoveTo getMoveDirection() const;
        bool isRunning();
        void listen();
};

#endif
