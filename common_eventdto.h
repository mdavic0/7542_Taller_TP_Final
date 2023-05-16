#ifndef COMMON_EVENTDTO_H_
#define COMMON_EVENTDTO_H_

#include "common_event.h"
#include "common_move.h"
#include <string>

class EventDTO {
    private:
        Event event;
        MoveTo moveTo;
        std::string str;
        uint32_t n;

    public:
        explicit EventDTO(
            Event event, MoveTo moveTo, const std::string& str, uint32_t n);

        Event getEvent() const;

        MoveTo getMoveTo() const;

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