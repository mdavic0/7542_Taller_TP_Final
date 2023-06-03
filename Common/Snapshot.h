#ifndef COMMON_SNAPSHOT_H_
#define COMMON_SNAPSHOT_H_

#include "Event.h"
#include "StOperator.h"
#include <utility>
#include <string>
#include <map>

class Snapshot {
    Event event;
    std::map<uint8_t, StOperator> playersInfo;
    TypeOperator typeOperator;
    uint32_t code;
    uint8_t ok;
    uint8_t idPlayer;


public:
    // CREATE 
    explicit Snapshot(const Event& event, const uint32_t& code, const uint8_t& idPlayer);
    // JOIN
    explicit Snapshot(const Event& event, const uint8_t& ok, const uint8_t& idPlayer);
    // PLAYING
    explicit Snapshot(const std::map<uint8_t, StOperator>& playersInfo);

    Event getEvent() const;

    TypeOperator getTypeOperator() const;

    uint32_t getCode() const;

    uint8_t getOk() const;

    uint8_t getIdPlayer() const;

    std::map<uint8_t, StOperator> getInfo() const;

    /*
     * No queremos permitir que alguien haga copias
     */
    Snapshot(const Snapshot&) = delete;
    Snapshot& operator=(const Snapshot&) = delete;

    Snapshot(Snapshot&&);
    Snapshot& operator=(Snapshot&&);
};

#endif  // COMMON_SNAPSHOT_H_
