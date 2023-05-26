#ifndef COMMON_SNAPSHOT_H_
#define COMMON_SNAPSHOT_H_

#include "common_event.h"
#include "common_type_operator.h"
#include <utility>
#include <string>
#include <map>

class Snapshot {
    Event event;
    std::map<TypeOperator, std::pair<uint16_t, uint16_t>> player_positions;
    TypeOperator typeOperator;
    uint32_t code;
    uint8_t ok;

public:
    explicit Snapshot(Event event, TypeOperator typeOperator, const uint32_t& code,
        const uint8_t& ok);
    explicit  Snapshot(std::map<TypeOperator, std::pair<uint16_t, uint16_t>>& players_position);
    explicit  Snapshot(std::map<TypeOperator, std::pair<uint16_t, uint16_t>>& players_position, Event event);

    Event getEvent() const;

    TypeOperator getTypeOperator() const;

    uint32_t getCode() const;

    uint8_t getOk() const;

    std::map<TypeOperator, std::pair<uint16_t, uint16_t>> getPositions() const;

    /*
     * No queremos permitir que alguien haga copias
     */
    Snapshot(const Snapshot&) = delete;
    Snapshot& operator=(const Snapshot&) = delete;

    Snapshot(Snapshot&&);
    Snapshot& operator=(Snapshot&&);
};

#endif  // COMMON_SNAPSHOT_H_
