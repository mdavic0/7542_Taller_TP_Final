#ifndef COMMON_SNAPSHOT_H_
#define COMMON_SNAPSHOT_H_

#include "common_event.h"
#include <string>

class Snapshot {
        Event event;
        uint32_t code;
        uint8_t ok;

    public:
        explicit Snapshot(
            Event event, uint32_t code, uint8_t ok);

        Event getEvent() const;

        uint32_t getCode() const;

        uint8_t getOk() const;

        /*
         * No queremos permitir que alguien haga copias
         */
         Snapshot(const Snapshot&) = delete;
         Snapshot& operator=(const Snapshot&) = delete;

         Snapshot(Snapshot&&);
         Snapshot& operator=(Snapshot&&);
};

#endif  // COMMON_SNAPSHOT_H_