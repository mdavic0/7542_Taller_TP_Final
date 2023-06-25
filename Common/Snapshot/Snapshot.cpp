#include "Snapshot.h"
#include <string>

Snapshot::Snapshot(const Event& event, const uint32_t& code, const uint8_t& idPlayer) : event(event), code(code),
    idPlayer(idPlayer), ok(0), size(0), typeOperator(TypeOperator::operator_idle),
    idMap(0), typeGame(TypeGame::game_idle), time(0), shots(0), kills(0) {}

Snapshot::Snapshot(const Event& event, const uint8_t& ok, const uint8_t& idPlayer, const uint8_t& size) : 
    event(event), ok(ok), idPlayer(idPlayer), code(0), size(size), typeOperator(TypeOperator::operator_idle),
    idMap(0), typeGame(TypeGame::game_idle), time(0), shots(0), kills(0) {}

Snapshot::Snapshot(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto>& enemies,
    const std::vector<ObstacleDto>& obstacles, const TypeGame& typeGame, const uint8_t& idMap) :
    event(Event::event_start_game), playersInfo(playersInfo), typeOperator(TypeOperator::operator_idle),
    code(0), ok(0), idPlayer(0), size(0), idMap(idMap), typeGame(typeGame), enemies(enemies),
    obstacles(obstacles), time(0), shots(0), kills(0) {}

Snapshot::Snapshot(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto>& enemies,
    const std::vector<GrenadeDto>& grenades, const bool& blitzAttacking) :
    event(Event::event_playing), playersInfo(playersInfo), typeOperator(TypeOperator::operator_idle), 
    code(0), ok(0), idPlayer(0), size(0), idMap(0), typeGame(TypeGame::game_idle), enemies(enemies),
    time(0), shots(0), kills(0), grenades(grenades), blitzAttacking(blitzAttacking) {}

Snapshot::Snapshot(const Event& event) : event(event), code(0),
    idPlayer(0), ok(0), size(0), typeOperator(TypeOperator::operator_idle),
    idMap(0), typeGame(TypeGame::game_idle), time(0), shots(0), kills(0) {}

Snapshot::Snapshot(const uint32_t& time, const uint16_t& shots, const uint8_t& kills) : event(Event::event_stats), code(0),
    idPlayer(0), ok(0), size(0), typeOperator(TypeOperator::operator_idle),
    idMap(0), typeGame(TypeGame::game_idle), time(time), shots(shots), kills(kills) {}

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

uint8_t Snapshot::getKills() const {
    return kills;
}

uint16_t Snapshot::getShots() const {
    return shots;
}

uint32_t Snapshot::getTime() const {
    return time;
}

std::vector<StOperator> Snapshot::getInfo() const {
    return playersInfo;
}

std::vector<EnemyDto> Snapshot::getEnemies() const {
    return enemies;
}

std::vector<ObstacleDto> Snapshot::getObstacles() const {
    return obstacles;
}

std::vector<GrenadeDto> Snapshot::getGrenades() const{
    return grenades;
}

bool Snapshot::getBlitzAttacking() const {
    return blitzAttacking;
}

Snapshot::Snapshot(Snapshot&& other) {
    this->event = other.event;
    this->typeOperator = other.typeOperator;
    this->code = other.code;
    this->ok = other.ok;
    this->size = other.size;
    this->idMap = other.idMap;
    this->kills = other.kills;
    this->shots = other.shots;
    this->time = other.time;
    this->playersInfo = other.playersInfo;
    this->enemies = other.enemies;
    this->typeGame = other.typeGame;
    this->obstacles = other.obstacles;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.size = 0;
    other.idMap = 0;
    other.kills = 0;
    other.shots = 0;
    other.time = 0;
    other.playersInfo = std::vector<StOperator> {};
    other.enemies = std::vector<EnemyDto> {};
    other.obstacles = std::vector<ObstacleDto> {};
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
    this->kills = other.kills;
    this->shots = other.shots;
    this->time = other.time;
    this->playersInfo = other.playersInfo;
    this->enemies = other.enemies;
    this->typeGame = other.typeGame;
    this->obstacles = other.obstacles;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.size = 0;
    other.idMap = 0;
    other.kills = 0;
    other.shots = 0;
    other.time = 0;
    other.playersInfo = std::vector<StOperator> {};
    other.enemies = std::vector<EnemyDto> {};
    other.obstacles = std::vector<ObstacleDto> {};

    return *this;
}
