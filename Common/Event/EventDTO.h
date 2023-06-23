#ifndef COMMON_EVENTDTO_H_
#define COMMON_EVENTDTO_H_

#include "Event.h"
#include "Move.h"
#include "TypeOperator.h"
#include "TypeGame.h"
#include "TypeDifficulty.h"
#include <string>

class EventDTO {
private:
    Event event;
    MoveTo moveTo;
    TypeOperator typeOperator;
    TypeGame typeGame;
    TypeDifficulty typeDifficulty;
    std::string str;
    uint32_t n; // code join
    uint8_t idPlayer;

public:
    // Event create
    explicit EventDTO(const std::string& name, const TypeGame& typeGame,
        const TypeOperator& typeOperator, const TypeDifficulty & typeDifficulty);

    // Event join
    explicit EventDTO(const uint32_t& code, const TypeOperator& typeOperator);

    // Event move or stop
    explicit EventDTO(const Event& event, const MoveTo& moveTo, const uint8_t& idPlayer);

    // Generic
    explicit EventDTO(const Event& event, const uint8_t& idPlayer);

    Event getEvent() const;

    MoveTo getMoveTo() const;

    TypeOperator getTypeOperator() const;

    TypeGame getTypeGame() const;

    TypeDifficulty getTypeDifficulty() const;

    std::string getStr() const;

    uint32_t getN() const;

    uint8_t getIdPlayer() const;

    /*
     * No queremos permitir que alguien haga copias
     */
    EventDTO(const EventDTO&) = delete;
    EventDTO& operator=(const EventDTO&) = delete;

    EventDTO(EventDTO&&);
    EventDTO& operator=(EventDTO&&);
};

#endif  // COMMON_EVENTDTO_H_