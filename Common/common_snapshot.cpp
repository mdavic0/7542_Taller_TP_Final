#include "common_snapshot.h"
#include <string>

Snapshot::Snapshot(Event event, TypeOperator typeOperator, const uint32_t& code,
        const uint8_t& ok, const uint16_t& x, const uint16_t& y) : event(event),
        typeOperator(typeOperator), code(code), ok(ok), position(x,y) {}

// TODO: HACER QUE PROTOCOLO MANDE EL SNAPSHOT CON TODOS LOS
//      TYPEOPERATOR Y TODAS LAS POSICIONES.
//     SERIA ALGO DEL ESTILO:
//              1Byte                 a definir                a definir
//     |cantidad de jugadores|  |cosas del jugador 1| .... |cosas del jugador n|
//      En un principio 'cosas del jugador i' van a ser el typeOp y la position
Snapshot::Snapshot(std::map<TypeOperator, std::pair<uint16_t, uint16_t>> &players_position) :
    event(Event::event_create), player_positions(players_position),
    typeOperator(players_position.begin()->first), code(0), ok(0) {
} // TODO: Ver como solucionar el event_create o event_join (de momento esta
//    hardcodeado el Event a event_create )

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