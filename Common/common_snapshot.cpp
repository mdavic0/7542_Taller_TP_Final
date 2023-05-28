#include "common_snapshot.h"
#include <string>

Snapshot::Snapshot(Event event, const uint32_t& code) : event(event), code(code),
    ok(0), typeOperator(TypeOperator::operator_idle) {}

Snapshot::Snapshot(Event event, const uint8_t& ok)  : event(event), ok(ok),
    code(0), typeOperator(TypeOperator::operator_idle) {}

// TODO: HACER QUE PROTOCOLO MANDE EL SNAPSHOT CON TODOS LOS
//      TYPEOPERATOR Y TODAS LAS POSICIONES.
//     SERIA ALGO DEL ESTILO:
//              1Byte                 a definir                a definir
//     |cantidad de jugadores|  |cosas del jugador 1| .... |cosas del jugador n|
//      En un principio 'cosas del jugador i' van a ser el typeOp y la position
Snapshot::Snapshot(std::map<TypeOperator, std::pair<uint16_t, uint16_t>> &players_position) :
    event(Event::event_playing), player_positions(players_position),
    typeOperator(TypeOperator::operator_idle), code(0), ok(0) {}


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

std::map<TypeOperator, std::pair<uint16_t, uint16_t>> Snapshot::getPositions() const {
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
    other.player_positions = std::map<TypeOperator, std::pair<uint16_t, uint16_t>> {};
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
    other.player_positions = std::map<TypeOperator, std::pair<uint16_t, uint16_t>> {};

    return *this;
}
