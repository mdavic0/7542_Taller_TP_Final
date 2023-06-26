#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include "Protocol.h"
#include "EventDTO.h"
#include "Snapshot.h"

/*
 * TDA ServerProtocol.
 * Se comunica con el cliente a través de su T.
 */
template <typename T>
class ServerProtocol : Protocol<T> {
    private:

EventDTO getCreate(std::shared_ptr<T> skt) {
    uint8_t idOperator;
    this->recvAll(&idOperator, 1, skt);
    TypeOperator op = TypeOperator::operator_idle;

    switch (idOperator) {
    case IDF_CODE:
        op = TypeOperator::operator_idf;
        break;
        
    case P90_CODE:
        op = TypeOperator::operator_p90;
        break;
        
    case SCOUT_CODE:
        op = TypeOperator::operator_scout;
        break;
    
    default:
        break;
    }

    uint8_t idGame;
    this->recvAll(&idGame, 1, skt);
    TypeGame game = TypeGame::game_idle;

    switch (idGame) {
    case SURVIVAL_CODE:
        game = TypeGame::game_survival;
        break;
        
    case CLEAR_ZONE_CODE:
        game = TypeGame::game_clear_zone;
        break;
    
    default:
        break;
    }

    uint8_t idDifficulty;
    this->recvAll(&idDifficulty, 1, skt);
    TypeDifficulty difficulty = TypeDifficulty::difficulty_idle;

    switch (idDifficulty) {
    case DIFFICULTY_IDLE:
        difficulty = TypeDifficulty::difficulty_idle;
        break;
        
    case DIFFICULTY_EASY:
        difficulty = TypeDifficulty::difficulty_easy;
        break;
        
    case DIFFICULTY_NORMAL:
        difficulty = TypeDifficulty::difficulty_normal;
        break;
        
    case DIFFICULTY_HARD:
        difficulty = TypeDifficulty::difficulty_hard;
        break;
        
    case DIFFICULTY_GOD:
        difficulty = TypeDifficulty::difficulty_god;
        break;
        
    }

    return EventDTO(this->recvString(skt), game, op, difficulty);
}

EventDTO getJoin(std::shared_ptr<T> skt) {
    uint8_t idOperator;
    this->recvAll(&idOperator, 1, skt);
    TypeOperator op = TypeOperator::operator_idle;

    switch (idOperator) {
    case IDF_CODE:
        op = TypeOperator::operator_idf;
        break;
        
    case P90_CODE:
        op = TypeOperator::operator_p90;
        break;
        
    case SCOUT_CODE:
        op = TypeOperator::operator_scout;
        break;
    
    default:
        break;
    }

    uint32_t code;
    this->recvAll(&code, 4, skt);
    code = ntohl(code);
  
    return EventDTO(code, op);

}

EventDTO getStart(std::shared_ptr<T> skt) {
    return EventDTO(Event::event_start_game, 0);
}

EventDTO getMove(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    uint8_t direction;
    this->recvAll(&direction, 1, skt);
    MoveTo moveTo = MoveTo::move_idle;

    switch (direction) {
    case UP_CODE:
        moveTo = MoveTo::move_up;
        break;
    
    case DOWN_CODE:
        moveTo = MoveTo::move_down;
        break;
        
    case RIGHT_CODE:
        moveTo = MoveTo::move_right;
        break;
        
    case LEFT_CODE:
        moveTo = MoveTo::move_left;
        break;

    default:
        break;
    }

    return EventDTO(Event::event_move, moveTo, id);
}

EventDTO getStopMove(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    uint8_t direction;
    this->recvAll(&direction, 1, skt);
    MoveTo moveTo = MoveTo::move_idle;

    switch (direction) {
    case UP_CODE:
        moveTo = MoveTo::move_up;
        break;
    
    case DOWN_CODE:
        moveTo = MoveTo::move_down;
        break;
        
    case RIGHT_CODE:
        moveTo = MoveTo::move_right;
        break;
        
    case LEFT_CODE:
        moveTo = MoveTo::move_left;
        break;

    default:
        break;
    }

    return EventDTO(Event::event_stop_move, moveTo, id);
}

EventDTO getSmoke(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_throw_smoke, id);
}

EventDTO getStopSmoke(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_smoke, id);
}

EventDTO getGrenade(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_throw_grenade, id);
}

EventDTO getStopGrenade(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_grenade, id);
}

EventDTO getBlitz(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_blitz_atack, id);
}

EventDTO getShoot(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_shoot, id);
}

EventDTO getStopShoot(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_shoot, id);
}

EventDTO getRecharge(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_recharge, id);
}

EventDTO getReanimate(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_reanimate, id);
}

EventDTO getStopReanimate(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_reanimate, id);
}

EventDTO getLeave(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_leave, id);
}

EventDTO getCheatFinish(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_cheat_finish_game, id);   
}

EventDTO getCheatMunition(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_cheat_infinite_munition, id);
}

EventDTO getCheatVelocity(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_cheat_more_velocity, id);
}

EventDTO getCheatKills(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_cheat_kill_enemies, id);
}

EventDTO getCheatHealth(std::shared_ptr<T> skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_cheat_infinite_health, id);
}

void sendCreate(const uint32_t& code, const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t event = CREATE_CODE;
    this->sendAll(&event, 1, skt);

    uint32_t aux = htonl(code);
    this->sendAll(&aux, 4, skt);

    this->sendAll(&idPlayer, 1, skt);
}

void sendJoin(const uint8_t& ok, const uint8_t& idPlayer,
    const uint8_t& size, std::shared_ptr<T> skt) {
    uint8_t event = JOIN_CODE;
    this->sendAll(&event, 1, skt);

    this->sendAll(&ok, 1, skt);

    if (ok == 0) {
        this->sendAll(&idPlayer, 1, skt);
        this->sendAll(&size, 1, skt);
    }
}

void sendStart(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto> &enemiesInfo,
    const std::vector<ObstacleDto> &obstaclesInfo, const TypeGame& typeGame, const uint8_t& idMap, std::shared_ptr<T> skt) {
    uint8_t event = START_CODE;
    this->sendAll(&event, 1, skt);
    
    sendPlayersInfo(playersInfo, skt);
    sendEnemiesInfo(enemiesInfo, skt);
    sendObstaclesInfo(obstaclesInfo, skt);
    
    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    this->sendAll(&idGame, 1, skt);

    this->sendAll(&idMap, 1, skt);
}

void sendPlaying(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto> &enemiesInfo,
    const std::vector<GrenadeDto> &grenadesInfo, const bool &blitzAttacking, std::shared_ptr<T> skt) {
    uint8_t event = PLAYING_CODE;
    this->sendAll(&event, 1, skt);

    sendPlayersInfo(playersInfo, skt);
    sendEnemiesInfo(enemiesInfo, skt);
    sendGrenades(grenadesInfo, skt);
    sendBoolean(blitzAttacking, skt);
}

void sendEnd(std::shared_ptr<T> skt) {
    uint8_t event = END_CODE;
    this->sendAll(&event, 1, skt);
}

void sendStats(const std::vector<StatsDto> &stats, std::shared_ptr<T> skt) {
    uint8_t event = STATS_CODE;
    this->sendAll(&event, 1, skt);

    uint8_t count = stats.size();
    this->sendAll(&count, 1, skt);
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        int8_t id = it->getPlayerId();
        this->sendAll(&id, 1, skt);

        int16_t aux_kills = htons(it->getKills());
        this->sendAll(&aux_kills, 2, skt);

        int32_t aux_rkg_kills = htonl(it->getRankingKills());
        this->sendAll(&aux_rkg_kills, 4, skt);

        int16_t aux_shots = htons(it->getShots());
        this->sendAll(&aux_shots, 2, skt);

        int32_t aux_rkg_shots = htonl(it->getRankingShots());
        this->sendAll(&aux_rkg_shots, 4, skt);

        int16_t aux_minutes = htons(it->getMinutes());
        this->sendAll(&aux_minutes, 2, skt);

        int16_t aux_seconds = htons(it->getSeconds());
        this->sendAll(&aux_seconds, 2, skt);

        int32_t aux_rkg_duration = htonl(it->getRankingDuration());
        this->sendAll(&aux_rkg_duration, 4, skt);
  }   
}

void sendTypeOperator(const TypeOperator& typeOperator, std::shared_ptr<T> skt) {
    if(typeOperator == TypeOperator::operator_idf){
        uint8_t op = IDF_CODE;
        this->sendAll(&op, 1, skt);
    } else if (typeOperator == TypeOperator::operator_p90) {
        uint8_t op = P90_CODE;
        this->sendAll(&op, 1, skt);
    } else if (typeOperator == TypeOperator::operator_scout) {
        uint8_t op = SCOUT_CODE;
        this->sendAll(&op, 1, skt);        
    }
}

void sendTypeInfected(const TypeInfected& typeInfected, std::shared_ptr<T> skt) {
    if(typeInfected == TypeInfected::infected_zombie){
        uint8_t inf = INFECTED_ZOMBIE;
        this->sendAll(&inf, 1, skt);
    } else if (typeInfected == TypeInfected::infected_jumper) {
        uint8_t inf = INFECTED_JUMPER;
        this->sendAll(&inf, 1, skt);
    } else if (typeInfected == TypeInfected::infected_witch) {
        uint8_t inf = INFECTED_WITCH;
        this->sendAll(&inf, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_spear) {
        uint8_t inf = INFECTED_SPEAR;
        this->sendAll(&inf, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_venom) {
        uint8_t inf = INFECTED_VENOM;
        this->sendAll(&inf, 1, skt);        
    }
}

void sendTypeObstacle(const TypeObstacle& typeObstacle, std::shared_ptr<T> skt) {
    if(typeObstacle == TypeObstacle::obstacle_tire){
        uint8_t ob = OBSTACLE_TIRE;
        this->sendAll(&ob, 1, skt);
    } else if (typeObstacle == TypeObstacle::obstacle_crater) {
        uint8_t ob = OBSTACLE_CRATER;
        this->sendAll(&ob, 1, skt);
    }
}

void sendTypeGrenade(const TypeGrenade& typeGrenade, std::shared_ptr<T> skt) {
    if(typeGrenade == TypeGrenade::grenade_explosive){
        uint8_t gre = GRENADE_EXPLOSIVE;
        this->sendAll(&gre, 1, skt);
    } else if (typeGrenade == TypeGrenade::grenade_smoke) {
        uint8_t gre = GRENADE_SMOKE;
        this->sendAll(&gre, 1, skt);
    }
}
        
void sendOperator(const TypeInfected& typeInfected, std::shared_ptr<T> skt) {
    if(typeInfected == TypeInfected::infected_zombie){
        uint8_t op = INFECTED_ZOMBIE;
        this->sendAll(&op, 1, skt);
    } else if (typeInfected == TypeInfected::infected_jumper) {
        uint8_t op = INFECTED_JUMPER;
        this->sendAll(&op, 1, skt);
    } else if (typeInfected == TypeInfected::infected_witch) {
        uint8_t op = INFECTED_WITCH;
        this->sendAll(&op, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_spear) {
        uint8_t op = INFECTED_SPEAR;
        this->sendAll(&op, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_venom) {
        uint8_t op = INFECTED_VENOM;
        this->sendAll(&op, 1, skt);
    }
}

void sendState(const State& state, std::shared_ptr<T> skt) {
    if(state == State::idle){
        uint8_t aux = STATE_IDLE;
        this->sendAll(&aux, 1, skt);
    } else if (state == State::moving) {
        uint8_t aux = STATE_MOVING;
        this->sendAll(&aux, 1, skt);
    } else if (state == State::atack) {
        uint8_t aux = STATE_ATACK;
        this->sendAll(&aux, 1, skt);       
    } else if (state == State::injure) {
        uint8_t aux = STATE_INJURE;
        this->sendAll(&aux, 1, skt);       
    } else if (state == State::hability) {
        uint8_t aux = STATE_HABILITY;
        this->sendAll(&aux, 1, skt);       
    } else if (state == State::recharge) {
        uint8_t aux = STATE_RECHARGE;
        this->sendAll(&aux, 1, skt);       
    }
}

void sendPlayersInfo(const std::vector<StOperator> &playersInfo, std::shared_ptr<T> skt) {
    uint8_t playersCount = playersInfo.size();
    this->sendAll(&playersCount, 1, skt);
    for (auto it = playersInfo.begin(); it != playersInfo.end(); ++it) {
        uint8_t id = it->getId();
        this->sendAll(&id, 1, skt);
        sendTypeOperator(it->getTypeOperator(), skt);
        sendState(it->getState(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
        uint8_t health = it->getHealth();
        this->sendAll(&health, 1, skt);
        uint8_t munition = it->getMunition();
        this->sendAll(&munition, 1, skt);
        sendBoolean(it->isGrenadeAvailable(), skt);
        sendBoolean(it->isSmokeAvailable(), skt);
  }
}

void sendEnemiesInfo(const std::vector<EnemyDto> &enemiesInfo, std::shared_ptr<T> skt) {
    uint8_t count = enemiesInfo.size();
    this->sendAll(&count, 1, skt);
    for (auto it = enemiesInfo.begin(); it != enemiesInfo.end(); ++it) {
        uint8_t id = it->getId();
        this->sendAll(&id, 1, skt);
        sendTypeInfected(it->getTypeInfected(), skt);
        sendState(it->getState(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
  }   
}


void sendObstaclesInfo(const std::vector<ObstacleDto> &obstaclesInfo, std::shared_ptr<T> skt) {
    uint8_t count = obstaclesInfo.size();
    this->sendAll(&count, 1, skt);
    for (auto it = obstaclesInfo.begin(); it != obstaclesInfo.end(); ++it) {
        uint8_t id = it->getId();
        this->sendAll(&id, 1, skt);
        sendTypeObstacle(it->getTypeObstacle(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
  }
} 

void sendGrenades(const std::vector<GrenadeDto> &grenadesInfo, std::shared_ptr<T> skt) {
    uint8_t countGrenades = grenadesInfo.size();
    this->sendAll(&countGrenades, 1, skt);
    for (auto it = grenadesInfo.begin(); it != grenadesInfo.end(); ++it) {
        sendTypeGrenade(it->getTypeGrenade(), skt);
        sendBoolean(it->alreadyExploded(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
  }

}

void sendPosition(const uint16_t& x, const uint16_t& y, std::shared_ptr<T> skt) {
    uint16_t xAux = htons(x);
    this->sendAll(&xAux, 2, skt);

    uint16_t yAux = htons(y);
    this->sendAll(&yAux, 2, skt);
}

void sendBoolean(const bool& inputBool, std::shared_ptr<T> skt) {
    if(inputBool) {
        uint8_t b = BOOL_TRUE;
        this->sendAll(&b, 1, skt);
    } else {
        uint8_t b = BOOL_FALSE;
        this->sendAll(&b, 1, skt);
    }
}

    public:
        /*
        * Constructor que llama al constructor del padre
        * */
        explicit ServerProtocol() {}

EventDTO getEvent(std::shared_ptr<T> skt) {
    uint8_t event;
    this->recvAll(&event, 1, skt);

    switch (event) {
    case CREATE_CODE:
        return getCreate(skt);
        break;
    
    case JOIN_CODE:
        return getJoin(skt);
        break;

    case START_CODE:
        return getStart(skt);
        break;
        
    case MOVE_CODE:
        return getMove(skt);
        break;
        
    case STOP_MOVE_CODE:
        return getStopMove(skt);
        break;

    case THROW_SMOKE_CODE:
        return getSmoke(skt);
        break;

    case STOP_SMOKE_CODE:
        return getStopSmoke(skt);
        break;

    case THROW_GRENADE_CODE:
        return getGrenade(skt);
        break;

    case STOP_GRENADE_CODE:
        return getStopGrenade(skt);
        break;

    case BLITZ_ATACK_CODE:
        return getBlitz(skt);
        break;

    case SHOOT_CODE:
        return getShoot(skt);
        break;

    case STOP_SHOOT_CODE:
        return getStopShoot(skt);
        break;

    case RECHARGE_CODE:
        return getRecharge(skt);
        break;

    case REANIMATE_CODE:
        return getReanimate(skt);
        break;

    case STOP_REANIMATE_CODE:
        return getStopReanimate(skt);
        break;

    case LEAVE_CODE:
        return getLeave(skt);
        break;

    case CHEAT_FINISH_GAME_CODE:
        return getCheatFinish(skt);
        break;

    case CHEAT_INFINITE_MUNITION_CODE:
        return getCheatMunition(skt);
        break;

    case CHEAT_MORE_VELOCITY_CODE:
        return getCheatVelocity(skt);
        break;

    case CHEAT_KILL_ENEMIES_CODE:
        return getCheatKills(skt);
        break;

    case CHEAT_INFINITE_HEALTH_CODE:
        return getCheatHealth(skt);
        break;

    default:
        break;
    }

    return EventDTO(Event::event_invalid, 0);
}

void sendSnapshot(std::shared_ptr<Snapshot>& snapshot, std::shared_ptr<T> skt) {
    Event event = snapshot->getEvent();
    if (event == Event::event_create) {
        sendCreate(snapshot->getCode(), snapshot->getIdPlayer(), skt);
    } else if (event == Event::event_join) {
        sendJoin(snapshot->getOk(), snapshot->getIdPlayer(), snapshot->getSize(), skt);
    } else if (event == Event::event_start_game) {
        sendStart(snapshot->getInfo(), snapshot->getEnemies(), snapshot->getObstacles(), snapshot->getTypeGame(), snapshot->getMap(), skt);
    } else if (event == Event::event_playing) {
        sendPlaying(snapshot->getInfo(), snapshot->getEnemies(), snapshot->getGrenades(), snapshot->getBlitzAttacking(), skt);
    } else if (event == Event::event_end) {
        sendEnd(skt);
    } else if (event == Event::event_stats) {
        sendStats(snapshot->getStats(), skt);
    }
}

        /*
         * No queremos permitir que alguien haga copias
         * */
        ServerProtocol(const ServerProtocol&) = delete;
        ServerProtocol& operator=(const ServerProtocol&) = delete;

        /*
         * Queremos permitir mover a los objetos (move semantics).
         *
         * Como todos nuestros atributos son movibles, la implementación
         * por default de C++ nos alcanza.
         * */
        ServerProtocol(ServerProtocol&&) = default;
        ServerProtocol& operator=(ServerProtocol&&) = default;
};

#endif  // SERVER_PROTOCOL_H_