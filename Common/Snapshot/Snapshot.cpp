#include "Snapshot.h"
#include <string>

Snapshot::Snapshot(const Event& event, const uint32_t& code, const uint8_t& idPlayer) : event(event), code(code),
    idPlayer(idPlayer), ok(0), size(0), typeOperator(TypeOperator::operator_idle),
    idMap(0), typeGame(TypeGame::game_idle) {}

Snapshot::Snapshot(const Event& event, const uint8_t& ok, const uint8_t& idPlayer, const uint8_t& size) : 
    event(event), ok(ok), idPlayer(idPlayer), code(0), size(size),
    typeOperator(TypeOperator::operator_idle), idMap(0), typeGame(TypeGame::game_idle) {}

Snapshot::Snapshot(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto>& enemies,
    const TypeGame& typeGame, const uint8_t& idMap) :
    event(Event::event_start_game), playersInfo(playersInfo), typeOperator(TypeOperator::operator_idle),
    code(0), ok(0), idPlayer(0), size(0), idMap(idMap), typeGame(typeGame), enemies(enemies) {}

Snapshot::Snapshot(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto>& enemies) :
    event(Event::event_playing), playersInfo(playersInfo), typeOperator(TypeOperator::operator_idle), 
    code(0), ok(0), idPlayer(0), size(0), idMap(0), typeGame(TypeGame::game_idle), enemies(enemies) {}


Event Snapshot::getEvent() const {
    return event;
}

TypeOperator Snapshot::getTypeOperator() const {
    return typeOperator;
}

TypeGame Snapshot::getTypeGame() const {
    return typeGame;
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

uint8_t Snapshot::getSize() const {
    return size;
}

uint8_t Snapshot::getMap() const {
    return idMap;
}

std::vector<StOperator> Snapshot::getInfo() const {
    return playersInfo;
}

std::vector<EnemyDto> Snapshot::getEnemies() const {
    return enemies;
}

Snapshot::Snapshot(Snapshot&& other) {
    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->size = other.size;
    this->idMap = other.idMap;
    this->playersInfo = other.playersInfo;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.size = 0;
    other.idMap = 0;
    other.playersInfo = std::vector<StOperator> {};
}

Snapshot& Snapshot::operator=(Snapshot&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->size = other.size;
    this->idMap = other.idMap;
    this->playersInfo = other.playersInfo;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.size = 0;
    other.idMap = 0;
    other.playersInfo = std::vector< StOperator> {};

    return *this;
}
