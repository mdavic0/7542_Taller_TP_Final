#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include "common_move.h"

class EventHandler {
    private:
        MoveTo moveDirection;
        bool running;
        void handleKeyDownEvent(SDL_Keysym keysym);
        void handleKeyUpEvent(SDL_Keysym keysym);
    public:
        EventHandler();
        ~EventHandler();
        MoveTo getMoveDirection() const;
        bool isRunning();
        void listen();
};

#endif
