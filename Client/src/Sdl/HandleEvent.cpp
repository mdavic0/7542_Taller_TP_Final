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
                this->eventQueue.push(
                    std::make_shared<EventDTO>(Event::event_leave, idPlayer));
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
            break;
        case SDLK_q:
            event = Event::event_throw_grenade;
            std::cout << "grenade\n";
            break;
        case SDLK_e:
            event = Event::event_throw_smoke;
            std::cout << "smoke\n";
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
            event = Event::event_stop_shoot;
            break;
        case SDLK_q:
            event = Event::event_stop_grenade;
            break;
        case SDLK_e:
            event = Event::event_stop_smoke;
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

