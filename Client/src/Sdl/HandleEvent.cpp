#include "HandleEvent.h"
#include "Event.h"
#include <iostream>

EventHandler::EventHandler(Queue<std::shared_ptr<EventDTO>>& eventQueue,
    uint8_t idPlayer, bool& endGame) : moveDirection(MoveTo::move_idle),
    running(true), eventQueue(eventQueue) , idPlayer(idPlayer),
    previousEvent(Event::event_playing), endGame(endGame) {
}

void EventHandler::listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->running = false;      // do not pop from snap queue
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
            break;
        case SDLK_e:
            event = Event::event_throw_smoke;
            break;
        case SDLK_f:
            event = Event::event_reanimate;
            break;
        case SDLK_r:
            event = Event::event_recharge;
            break;
        case SDLK_F1:
            event = Event::event_cheat_finish_game;
            break;
        case SDLK_F2:
            event = Event::event_cheat_more_velocity;
            break;
        case SDLK_F3:
            event = Event::event_cheat_kill_enemies;
            break;
        case SDLK_F4:
            event = Event::event_cheat_infinite_health;
            break;
         case SDLK_F5:
            event = Event::event_cheat_infinite_health;
            break;
        case SDLK_RETURN:
            if (endGame) {
                this->running = false;
            }
            break;
        default:
            moveDirection = MoveTo::move_idle;
            break;
    }
    if (!endGame) {
        if ((event != previousEvent and moveDirection != MoveTo::move_idle) or
            (event == previousEvent and event == Event::event_move and moveDirection != MoveTo::move_idle) or
            (event == previousEvent and event == Event::event_shoot and moveDirection != MoveTo::move_idle)) {
            this->previousEvent = event;
            this->eventQueue.push(std::make_shared<EventDTO>(event, moveDirection, idPlayer));
        }
    }
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
    if (!endGame) {
        if (moveDirection != MoveTo::move_idle) {
            this->previousEvent = event;
            this->eventQueue.push(std::make_shared<EventDTO>(event, moveDirection, idPlayer));
        }
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

