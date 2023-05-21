#ifndef COMMON_EVENTDTO_H_
#define COMMON_EVENTDTO_H_

#include "common_event.h"
#include "common_move.h"
#include "common_type_operator.h"
#include "common_type_game.h"
#include <string>

class EventDTO {
private:
    Event event;
    MoveTo moveTo;
    TypeOperator typeOperator;
    TypeGame typeGame;
    std::string str;
    uint32_t n; // code join

public:
    explicit EventDTO(Event event, MoveTo moveTo, TypeOperator typeOperator, TypeGame typeGame,
         const std::string& str, const uint32_t& n);
    
    // Event create
    EventDTO(Event event, const std::string& name, TypeGame typeGame, TypeOperator typeOperator);

    // Event join
    EventDTO(Event event, uint32_t code, TypeOperator typeOperator);

    Event getEvent() const;

    MoveTo getMoveTo() const;

    TypeOperator getTypeOperator() const;

    TypeGame getTypeGame() const;

    std::string getStr() const;

    uint32_t getN() const;

    /*
     * No queremos permitir que alguien haga copias
     */
    EventDTO(const EventDTO&) = delete;
    EventDTO& operator=(const EventDTO&) = delete;

    EventDTO(EventDTO&&);
    EventDTO& operator=(EventDTO&&);
};

#endif  // COMMON_EVENTDTO_H_