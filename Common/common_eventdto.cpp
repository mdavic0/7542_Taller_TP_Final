#include "common_eventdto.h"

EventDTO::EventDTO(Event event, const std::string& str, uint32_t n):
    event(event), str(str), n(n) {}

Event EventDTO::getEvent() const {
    return event;
}

MoveTo EventDTO::getMoveTo() const {
    return moveTo;
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
    this->str = other.str;
    this->n = other.n;

    other.event = Event::event_invalid;
    other.str = "";
    other.n = 0;
}

EventDTO& EventDTO::operator=(EventDTO&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->moveTo = other.moveTo;
    this->str = other.str;
    this->n = other.n;

    other.event = Event::event_invalid;
    other.str = "";
    other.n = 0;

    return *this;
}