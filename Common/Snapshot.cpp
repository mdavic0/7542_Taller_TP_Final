#include "Snapshot.h"
#include <string>

Snapshot::Snapshot(Event event, const uint32_t& code, const uint8_t& idPlayer) : event(event), code(code),
    idPlayer(idPlayer), ok(0), typeOperator(TypeOperator::operator_idle) {}

Snapshot::Snapshot(Event event, const uint8_t& ok, const uint8_t& idPlayer)  : event(event), ok(ok),
    idPlayer(idPlayer), code(0), typeOperator(TypeOperator::operator_idle) {}

Snapshot::Snapshot(std::map<uint8_t, std::pair<uint16_t, uint16_t>> &players_position) :
    event(Event::event_playing), player_positions(players_position),
    typeOperator(TypeOperator::operator_idle), code(0), ok(0), idPlayer(0) {}


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

uint8_t Snapshot::getIdPlayer() const {
    return idPlayer;
}

std::map<uint8_t, std::pair<uint16_t, uint16_t>> Snapshot::getPositions() const {
    return player_positions;
}

Snapshot::Snapshot(Snapshot&& other) {
    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->player_positions = other.player_positions;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.player_positions = std::map<uint8_t, std::pair<uint16_t, uint16_t>> {};
}

Snapshot& Snapshot::operator=(Snapshot&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->player_positions = other.player_positions;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.player_positions = std::map<uint8_t, std::pair<uint16_t, uint16_t>> {};

    return *this;
}
