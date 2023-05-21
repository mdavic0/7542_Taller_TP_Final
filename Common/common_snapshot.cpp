#include "common_snapshot.h"
#include <string>

Snapshot::Snapshot(Event event, TypeOperator typeOperator, const uint32_t& code,
        const uint8_t& ok, const uint16_t& x, const uint16_t& y) : event(event),
        typeOperator(typeOperator), code(code), ok(ok), position(x,y) {}

Event Snapshot::getEvent() const {
    return event;
}

TypeOperator Snapshot::getTypeOperator() const {
    return typeOperator;
}

uint32_t Snapshot::getCode() const {
    return code;
}

uint8_t Snapshot::getOk() const {
    return ok;
}

std::pair<uint16_t, uint16_t> Snapshot::getPosition() const {
    return position;
}

Snapshot::Snapshot(Snapshot&& other) {
    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->position = other.position;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
}

Snapshot& Snapshot::operator=(Snapshot&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->position = other.position;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;

    return *this;
}