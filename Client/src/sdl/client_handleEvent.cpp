#include "client_handleEvent.h"
#include "common_event.h"
#include <iostream>

EventHandler::EventHandler(Queue<EventDTO*>& eventQueue) : moveDirection(MoveTo::move_idle),
    running(true), eventQueue(eventQueue) {
}

void EventHandler::listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->running = false;
                std::cout << "Cerre el juego\n";
                break;
            case SDL_KEYDOWN:
                handleKeyDownEvent(event.key.keysym);
                break;
            case SDL_KEYUP:
                handleKeyUpEvent(event.key.keysym);
                break;
            default:
                break;
        }
    }
}

void EventHandler::handleKeyDownEvent(SDL_Keysym keysym) {
    switch(keysym.sym) {
        case SDLK_w:
            moveDirection = MoveTo::move_up;
            break;
        case SDLK_s:
            moveDirection = MoveTo::move_down;
            break;
        case SDLK_a:
            moveDirection = MoveTo::move_left;
            break;
        case SDLK_d:
            moveDirection = MoveTo::move_right;
            break;
        default:
            moveDirection = MoveTo::move_idle;
            break;
    }
    this->eventQueue.push(new EventDTO(Event::event_move, moveDirection));
}

void EventHandler::handleKeyUpEvent(SDL_Keysym keysym) {
    switch(keysym.sym) {
        case SDLK_w:
        case SDLK_s:
        case SDLK_a:
        case SDLK_d:
            moveDirection = MoveTo::move_idle;
            break;
        default:
            moveDirection = MoveTo::move_idle;
            break;
    }

}

MoveTo EventHandler::getMoveDirection() const {
    return this->moveDirection;
}
 
bool EventHandler::isRunning() {
    return this->running;
}

EventHandler::~EventHandler() {
}

