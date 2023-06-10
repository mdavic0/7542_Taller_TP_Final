#ifndef COMMON_SNAPSHOT_H_
#define COMMON_SNAPSHOT_H_

#include "Event.h"
#include "OperatorDto.h"
#include "TypeGame.h"
#include <utility>
#include <string>
#include <vector>

class Snapshot {
    Event event;
    std::vector<StOperator> playersInfo;
    TypeOperator typeOperator;
    TypeGame typeGame;
    uint32_t code;
    uint8_t ok;
    uint8_t idPlayer;
    uint8_t size;
    uint8_t idMap;

public:
    // CREATE 
    explicit Snapshot(const Event& event, const uint32_t& code, const uint8_t& idPlayer);
    // JOIN
    explicit Snapshot(const Event& event, const uint8_t& ok, const uint8_t& idPlayer, const uint8_t& size);
    // START
    explicit Snapshot(const std::vector<StOperator>& playersInfo, const TypeGame& typeGame, const uint8_t& idMap);
    // PLAYING
    explicit Snapshot(const std::vector<StOperator>& playersInfo);

    Event getEvent() const;

    TypeOperator getTypeOperator() const;

    TypeGame getTypeGame () const;

    uint32_t getCode() const;

    uint8_t getOk() const;

    uint8_t getIdPlayer() const;

    uint8_t getSize() const;

    uint8_t getMap() const;

    std::vector<StOperator> getInfo() const;

    /*
     * No queremos permitir que alguien haga copias
     */
    Snapshot(const Snapshot&) = delete;
    Snapshot& operator=(const Snapshot&) = delete;

    Snapshot(Snapshot&&);
    Snapshot& operator=(Snapshot&&);
};

#endif  // COMMON_SNAPSHOT_H_
