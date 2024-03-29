#include "EventDTO.h"

EventDTO::EventDTO(const std::string& name, const TypeGame& typeGame,
    const TypeOperator& typeOperator, const TypeDifficulty & typeDifficulty) : 
    event(Event::event_create), moveTo(MoveTo::move_idle), typeOperator(typeOperator),
    typeGame(typeGame), str(name), n(-1), idPlayer(0), typeDifficulty(typeDifficulty) {}

EventDTO::EventDTO(const uint32_t& code, const TypeOperator& typeOperator) : 
    event(Event::event_join), moveTo(MoveTo::move_idle), typeOperator(typeOperator),
    typeGame(TypeGame::game_idle), str(), n(code), idPlayer(0),
    typeDifficulty(TypeDifficulty::difficulty_idle) {}

EventDTO::EventDTO(const Event& event, const MoveTo& moveTo, const uint8_t& idPlayer) : 
    event(event), moveTo(moveTo), typeOperator(TypeOperator::operator_idle),
    typeGame(TypeGame::game_idle), str(), n(0), idPlayer(idPlayer),
    typeDifficulty(TypeDifficulty::difficulty_idle) {}

EventDTO::EventDTO(const Event& event, const uint8_t& idPlayer) : 
    event(event), moveTo(MoveTo::move_idle), typeOperator(TypeOperator::operator_idle),
    typeGame(TypeGame::game_idle), str(), n(0), idPlayer(idPlayer),
    typeDifficulty(TypeDifficulty::difficulty_idle) {}


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

TypeDifficulty EventDTO::getTypeDifficulty() const {
    return typeDifficulty;
}

std::string EventDTO::getStr() const {
    return str;
}

uint32_t EventDTO::getN() const {
    return n;
}

uint8_t EventDTO::getIdPlayer() const {
    return idPlayer;
}

EventDTO::EventDTO(EventDTO&& other) {
    this->event = other.event;
    this->moveTo = other.moveTo;
    this->typeOperator = other.typeOperator;
    this->typeGame = other.typeGame;
    this->typeDifficulty = other.typeDifficulty;
    this->str = other.str;
    this->n = other.n;
    this->idPlayer = other.idPlayer;

    other.event = Event::event_invalid;
    other.moveTo = MoveTo::move_idle;
    other.typeOperator = TypeOperator::operator_idle;
    other.typeGame = TypeGame::game_idle;
    other.typeDifficulty = TypeDifficulty::difficulty_idle;
    other.str = "";
    other.n = 0;
    other.idPlayer = 0;
}

EventDTO& EventDTO::operator=(EventDTO&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->moveTo = other.moveTo;
    this->typeOperator = other.typeOperator;
    this->typeGame = other.typeGame;
    this->typeDifficulty = other.typeDifficulty;
    this->str = other.str;
    this->n = other.n;
    this->idPlayer = other.idPlayer;

    other.event = Event::event_invalid;
    other.moveTo = MoveTo::move_idle;
    other.typeOperator = TypeOperator::operator_idle;
    other.typeGame = TypeGame::game_idle;
    other.typeDifficulty = TypeDifficulty::difficulty_idle;
    other.str = "";
    other.n = 0;
    other.idPlayer = 0;

    return *this;
}