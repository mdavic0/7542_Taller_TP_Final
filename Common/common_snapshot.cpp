#include "common_snapshot.h"
#include <string>
#include <iostream>
#include <sstream>

Snapshot::Snapshot(Event event, uint32_t code, uint8_t ok) :
    event(event), code(code), ok(ok) {}

Event Snapshot::getEvent() const {
    return event;
}

uint32_t Snapshot::getCode() const {
    return code;
}

uint8_t Snapshot::getOk() const {
    return ok;
}

Snapshot::Snapshot(Snapshot&& other) {
    this->event = other.event;
    this->code = other.code;
    this->ok = other.ok;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
}

Snapshot& Snapshot::operator=(Snapshot&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->code = other.code;
    this->ok = other.ok;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;

    return *this;
}