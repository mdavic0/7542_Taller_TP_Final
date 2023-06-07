#include "HandleEvent.h"
#include "Event.h"
#include <iostream>

EventHandler::EventHandler(Queue<std::shared_ptr<EventDTO>>& eventQueue,
    uint8_t idPlayer) : moveDirection(MoveTo::move_idle),
    running(true), eventQueue(eventQueue) , idPlayer(idPlayer) {
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
    Event event = Event::event_move;
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
        case SDLK_SPACE:
            event = Event::event_shoot;
            std::cout << "shooting\n";
            break;
        default:
            moveDirection = MoveTo::move_idle;
            break;
    }
    if (moveDirection != MoveTo::move_idle)
        this->eventQueue.push(std::make_shared<EventDTO>(event, moveDirection, idPlayer));
}

void EventHandler::handleKeyUpEvent(SDL_Keysym keysym) {
    Event event = Event::event_stop_move;
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
        case SDLK_SPACE:
            event = Event::event_stop_shooting;
            break;
        default:
            moveDirection = MoveTo::move_idle;
            break;
    }
    if (moveDirection != MoveTo::move_idle)
        this->eventQueue.push(std::make_shared<EventDTO>(event, moveDirection, idPlayer));
}

MoveTo EventHandler::getMoveDirection() const {
    return this->moveDirection;
}
 
bool EventHandler::isRunning() {
    return this->running;
}

EventHandler::~EventHandler() {
}

