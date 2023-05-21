#include "common_eventdto.h"

EventDTO::EventDTO(Event event, MoveTo moveTo, TypeOperator typeOperator, TypeGame typeGame,
    const std::string& str, const uint32_t& n) : event(event), moveTo(moveTo),
    typeOperator(typeOperator), typeGame(typeGame), str(str), n(n) {}

Event EventDTO::getEvent() const {
    return event;
}

MoveTo EventDTO::getMoveTo() const {
    return moveTo;
}

TypeOperator EventDTO::getTypeOperator() const {
    return typeOperator;   
}

TypeGame EventDTO::getTypeGame() const {
    return typeGame;
}

std::string EventDTO::getStr() const {
    return str;
}

uint32_t EventDTO::getN() const {
    return n;
}

EventDTO::EventDTO(EventDTO&& other) {
    this->event = other.event;
    this->moveTo = other.moveTo;
    this->typeOperator = other.typeOperator;
    this->typeGame = other.typeGame;
    this->str = other.str;
    this->n = other.n;

    other.event = Event::event_invalid;
    other.moveTo = MoveTo::move_idle;
    other.str = "";
    other.n = 0;
}

EventDTO& EventDTO::operator=(EventDTO&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->moveTo = other.moveTo;
    this->typeOperator = other.typeOperator;
    this->typeGame = other.typeGame;
    this->str = other.str;
    this->n = other.n;

    other.event = Event::event_invalid;
    other.moveTo = MoveTo::move_idle;
    other.str = "";
    other.n = 0;

    return *this;
}