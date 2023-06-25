#ifndef COMMON_SNAPSHOT_H_
#define COMMON_SNAPSHOT_H_

#include "Event.h"
#include "OperatorDto.h"
#include "ObstacleDto.h"
#include "TypeGame.h"
#include "EnemyDto.h"
#include "GrenadeDto.h"
#include <utility>
#include <string>
#include <vector>

class Snapshot {
    Event event;
    std::vector<StOperator> playersInfo;
    std::vector<EnemyDto> enemies;
    std::vector<ObstacleDto> obstacles;
    std::vector<GrenadeDto> grenades;
    bool blitzAttacking;
    TypeOperator typeOperator;
    TypeGame typeGame;
    uint32_t code;
    uint8_t ok;
    uint8_t idPlayer;
    uint8_t size;
    uint8_t idMap;

    uint8_t kills;
    uint16_t shots;
    uint32_t time; //seconds

public:
    // CREATE 
    explicit Snapshot(const Event& event, const uint32_t& code, const uint8_t& idPlayer);
    // JOIN
    explicit Snapshot(const Event& event, const uint8_t& ok, const uint8_t& idPlayer, const uint8_t& size);
    // START
    explicit Snapshot(const std::vector<StOperator>& playersInfo, const std::vector<EnemyDto>& enemies,
                      const std::vector<ObstacleDto>& obstacles, const TypeGame& typeGame, const uint8_t& idMap);
    // PLAYING
    explicit Snapshot(const std::vector<StOperator>& playersInfo, const std::vector<EnemyDto>& enemies,
        const std::vector<GrenadeDto>& grenades, const bool& blitzAttacking);

    // GENERIC
    explicit Snapshot(const Event& event);

    // STATS
    explicit Snapshot(const uint32_t& time, const uint16_t& shots, const uint8_t& kills);

    Event getEvent() const;

    TypeOperator getTypeOperator() const;

    TypeGame getTypeGame () const;

    uint32_t getCode() const;

    uint8_t getOk() const;

    uint8_t getIdPlayer() const;

    uint8_t getSize() const;

    uint8_t getMap() const;

    uint8_t getKills() const;
    
    uint16_t getShots() const;

    uint32_t getTime() const;

    std::vector<StOperator> getInfo() const;

    std::vector<EnemyDto> getEnemies() const;

    std::vector<ObstacleDto> getObstacles() const;

    std::vector<GrenadeDto> getGrenades() const;

    bool getBlitzAttacking() const;

    /*
     * No queremos permitir que alguien haga copias
     */
    Snapshot(const Snapshot&) = delete;
    Snapshot& operator=(const Snapshot&) = delete;

    Snapshot(Snapshot&&);
    Snapshot& operator=(Snapshot&&);
};

#endif  // COMMON_SNAPSHOT_H_
