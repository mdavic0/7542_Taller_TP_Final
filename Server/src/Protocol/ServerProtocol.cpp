/*#include "ServerProtocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>

ServerProtocol::ServerProtocol() : Protocol() { }

EventDTO ServerProtocol::getCreate(Socket *skt) {
    uint8_t idOperator;
    recvAll(&idOperator, 1, skt);
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
    recvAll(&idGame, 1, skt);
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

    return EventDTO(recvString(skt), game, op);
}

EventDTO ServerProtocol::getJoin(Socket *skt) {
    uint8_t idOperator;
    recvAll(&idOperator, 1, skt);
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
    recvAll(&code, 4, skt);
    code = ntohl(code);
  
    return EventDTO(code, op);

}

EventDTO ServerProtocol::getStart(Socket *skt) {
    return EventDTO(Event::event_start_game, 0);
}

EventDTO ServerProtocol::getMove(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    uint8_t direction;
    recvAll(&direction, 1, skt);
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

EventDTO ServerProtocol::getStopMove(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    uint8_t direction;
    recvAll(&direction, 1, skt);
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

EventDTO ServerProtocol::getSmoke(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_throw_smoke, id);
}

EventDTO ServerProtocol::getStopSmoke(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_smoke, id);
}

EventDTO ServerProtocol::getGrenade(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_throw_grenade, id);
}

EventDTO ServerProtocol::getStopGrenade(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_grenade, id);
}

EventDTO ServerProtocol::getBlitz(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_blitz_atack, id);
}

EventDTO ServerProtocol::getShoot(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_shoot, id);
}

EventDTO ServerProtocol::getStopShoot(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_shoot, id);
}

EventDTO ServerProtocol::getLeave(Socket *skt) {
    uint8_t id;
    recvAll(&id, 1, skt);

    return EventDTO(Event::event_leave, id);
}

void ServerProtocol::sendCreate(const uint32_t& code, const uint8_t& idPlayer, Socket *skt) {
    uint8_t event = CREATE_CODE;
    sendAll(&event, 1, skt);

    uint32_t aux = htonl(code);
    sendAll(&aux, 4, skt);

    sendAll(&idPlayer, 1, skt);
}

void ServerProtocol::sendJoin(const uint8_t& ok, const uint8_t& idPlayer,
    const uint8_t& size, Socket *skt) {
    uint8_t event = JOIN_CODE;
    sendAll(&event, 1, skt);

    sendAll(&ok, 1, skt);

    if (ok == 0) {
        sendAll(&idPlayer, 1), skt;
        sendAll(&size, 1, skt);
    }
}

void ServerProtocol::sendStart(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto> &enemiesInfo,
    const std::vector<ObstacleDto> &obstaclesInfo, const TypeGame& typeGame, const uint8_t& idMap, Socket *skt) {
    uint8_t event = START_CODE;
    sendAll(&event, 1, skt);
    
    sendPlayersInfo(playersInfo, skt);
    sendEnemiesInfo(enemiesInfo, skt);
    sendObstaclesInfo(obstaclesInfo, skt);
    
    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    sendAll(&idGame, 1, skt);

    sendAll(&idMap, 1, skt);
}

void ServerProtocol::sendPlaying(const std::vector<StOperator> &playersInfo,
    const std::vector<EnemyDto> &enemiesInfo, Socket *skt) {
    uint8_t event = PLAYING_CODE;
    sendAll(&event, 1);

    sendPlayersInfo(playersInfo, skt);
    sendEnemiesInfo(enemiesInfo, skt);
}

void ServerProtocol::sendEnd() {
    uint8_t event = END_CODE;
    sendAll(&event, 1);
}

void ServerProtocol::sendStats(const uint32_t& time, const uint16_t& shots, const uint8_t& kills) {
    uint8_t event = STATS_CODE;
    sendAll(&event, 1);

    uint16_t aux_time = htonl(time);
    sendAll(&aux_time, 4);

    uint16_t aux_shots = htons(shots);
    sendAll(&aux_shots, 2);

    sendAll(&kills, 1, skt);
}

void ServerProtocol::sendTypeOperator(const TypeOperator& typeOperator, Socket *skt) {
    if(typeOperator == TypeOperator::operator_idf){
        uint8_t op = IDF_CODE;
        sendAll(&op, 1, skt);
    } else if (typeOperator == TypeOperator::operator_p90) {
        uint8_t op = P90_CODE;
        sendAll(&op, 1, skt);
    } else if (typeOperator == TypeOperator::operator_scout) {
        uint8_t op = SCOUT_CODE;
        sendAll(&op, 1, skt);        
    }
}

void ServerProtocol::sendTypeInfected(const TypeInfected& typeInfected, Socket *skt) {
    if(typeInfected == TypeInfected::infected_zombie){
        uint8_t inf = INFECTED_ZOMBIE;
        sendAll(&inf, 1, skt);
    } else if (typeInfected == TypeInfected::infected_jumper) {
        uint8_t inf = INFECTED_JUMPER;
        sendAll(&inf, 1, skt);
    } else if (typeInfected == TypeInfected::infected_witch) {
        uint8_t inf = INFECTED_WITCH;
        sendAll(&inf, 1), skt;        
    } else if (typeInfected == TypeInfected::infected_spear) {
        uint8_t inf = INFECTED_SPEAR;
        sendAll(&inf, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_venom) {
        uint8_t inf = INFECTED_VENOM;
        sendAll(&inf, 1, skt);        
    }
}

void ServerProtocol::sendTypeObstacle(const TypeObstacle& typeObstacle, Socket *skt) {
    if(typeObstacle == TypeObstacle::obstacle_tire){
        uint8_t ob = OBSTACLE_TIRE;
        sendAll(&ob, 1, skt);
    } else if (typeObstacle == TypeObstacle::obstacle_crater) {
        uint8_t ob = OBSTACLE_CRATER;
        sendAll(&ob, 1, skt);
        
void ServerProtocol::sendOperator(const TypeInfected& typeInfected, Socket *skt) {
    if(typeInfected == TypeInfected::infected_zombie){
        uint8_t op = INFECTED_ZOMBIE;
        sendAll(&op, 1, skt);
    } else if (typeInfected == TypeInfected::infected_jumper) {
        uint8_t op = INFECTED_JUMPER;
        sendAll(&op, 1, skt);
    } else if (typeInfected == TypeInfected::infected_witch) {
        uint8_t op = INFECTED_WITCH;
        sendAll(&op, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_spear) {
        uint8_t op = INFECTED_SPEAR;
        sendAll(&op, 1, skt);        
    } else if (typeInfected == TypeInfected::infected_venom) {
        uint8_t op = INFECTED_VENOM;
        sendAll(&op, 1, skt);
    }
}

void ServerProtocol::sendState(const State& state, Socket *skt) {
    if(state == State::idle){
        uint8_t aux = STATE_IDLE;
        sendAll(&aux, 1, skt);
    } else if (state == State::moving) {
        uint8_t aux = STATE_MOVING;
        sendAll(&aux, 1, skt);
    } else if (state == State::atack) {
        uint8_t aux = STATE_ATACK;
        sendAll(&aux, 1, skt);       
    } else if (state == State::injure) {
        uint8_t aux = STATE_INJURE;
        sendAll(&aux, 1, skt);       
    } else if (state == State::hability) {
        uint8_t aux = STATE_HABILITY;
        sendAll(&aux, 1, skt);       
    } else if (state == State::recharge) {
        uint8_t aux = STATE_RECHARGE;
        sendAll(&aux, 1, skt);       
    }
}

void ServerProtocol::sendPlayersInfo(const std::vector<StOperator> &playersInfo, Socket *skt) {
    uint8_t playersCount = playersInfo.size();
    sendAll(&playersCount, 1, skt);
    for (auto it = playersInfo.begin(); it != playersInfo.end(); ++it) {
        uint8_t id = it->getId();
        sendAll(&id, 1, skt);
        sendTypeOperator(it->getTypeOperator(), skt);
        sendState(it->getState(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
        uint8_t health = it->getHealth();
        sendAll(&health, 1, skt);
        uint8_t munition = it->getMunition();
        sendAll(&munition, 1, skt);
  }
}

void ServerProtocol::sendEnemiesInfo(const std::vector<EnemyDto> &enemiesInfo, Socket *skt) {
    uint8_t count = enemiesInfo.size();
    sendAll(&count, 1, skt);
    for (auto it = enemiesInfo.begin(); it != enemiesInfo.end(); ++it) {
        uint8_t id = it->getId();
        sendAll(&id, 1, skt);
        sendTypeInfected(it->getTypeInfected(), skt);
        sendState(it->getState(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
  }   
}


void ServerProtocol::sendObstaclesInfo(const std::vector<ObstacleDto> &obstaclesInfo, Socket *skt) {
    uint8_t count = obstaclesInfo.size();
    sendAll(&count, 1, skt);
    for (auto it = obstaclesInfo.begin(); it != obstaclesInfo.end(); ++it) {
        uint8_t id = it->getId();
        sendAll(&id, 1, skt);
        sendTypeObstacle(it->getTypeObstacle(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
  }
}   

void ServerProtocol::sendPosition(const uint16_t& x, const uint16_t& y, Socket *skt) {
    uint16_t xAux = htons(x);
    sendAll(&xAux, 2, skt);

    uint16_t yAux = htons(y);
    sendAll(&yAux, 2, skt);
}

EventDTO ServerProtocol::getEvent(Socket *skt) {
    uint8_t event;
    recvAll(&event, 1, skt);

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
        return getSmoke(skt);
        break;

    case STOP_GRENADE_CODE:
        return getStopSmoke(skt);
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

    case LEAVE_CODE:
        return getLeave(skt);
        break;

    default:
        break;
    }

    return EventDTO(Event::event_invalid, 0);
}

void ServerProtocol::sendSnapshot(std::shared_ptr<Snapshot>& snapshot, Socket *skt) {
    Event event = snapshot->getEvent();
    if (event == Event::event_create) {
        sendCreate(snapshot->getCode(), snapshot->getIdPlayer(), skt);
    } else if (event == Event::event_join) {
        sendJoin(snapshot->getOk(), snapshot->getIdPlayer(), snapshot->getSize(), skt);
    } else if (event == Event::event_start_game) {
        sendStart(snapshot->getInfo(), snapshot->getEnemies(), snapshot->getObstacles(), snapshot->getTypeGame(), snapshot->getMap(), skt);
    } else if (event == Event::event_playing) {
        sendPlaying(snapshot->getInfo(), snapshot->getEnemies(), skt);
    } else if (event == Event::event_end) {
        sendEnd(skt);
    } else if (event == Event::event_stats) {
        sendStats(snapshot->getTime(), snapshot->getShots(), snapshot->getKills(), skt);
    }
}

*/