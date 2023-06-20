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
    
EventDTO getCreate(T *skt) {
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

    return EventDTO(this->recvString(skt), game, op);
}

EventDTO getJoin(T *skt) {
    uint8_t idOperator;
    this->recvAll(&idOperator, 1, skt);
    std::cout << "op " << (int)idOperator << std::endl;
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
    
    std::cout << "code 1 " << code << std::endl;
    code = ntohl(code);
    std::cout << "code 2 " << code << std::endl;

    return EventDTO(code, op);

}

EventDTO getStart(T *skt) {
    return EventDTO(Event::event_start_game, 0);
}

EventDTO getMove(T *skt) {
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

EventDTO getStopMove(T *skt) {
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

EventDTO getSmoke(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_throw_smoke, id);
}

EventDTO getStopSmoke(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_smoke, id);
}

EventDTO getGrenade(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_throw_grenade, id);
}

EventDTO getStopGrenade(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_grenade, id);
}

EventDTO getBlitz(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_blitz_atack, id);
}

EventDTO getShoot(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_shoot, id);
}

EventDTO getStopShoot(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_stop_shoot, id);
}

EventDTO getLeave(T *skt) {
    uint8_t id;
    this->recvAll(&id, 1, skt);

    return EventDTO(Event::event_leave, id);
}

void sendCreate(const uint32_t& code, const uint8_t& idPlayer, T *skt) {
    uint8_t event = CREATE_CODE;
    this->sendAll(&event, 1, skt);

    uint32_t aux = htonl(code);
    this->sendAll(&aux, 4, skt);

    this->sendAll(&idPlayer, 1, skt);
}

void sendJoin(const uint8_t& ok, const uint8_t& idPlayer,
    const uint8_t& size, T *skt) {
    uint8_t event = JOIN_CODE;
    this->sendAll(&event, 1, skt);

    this->sendAll(&ok, 1, skt);

    if (ok == 0) {
        this->sendAll(&idPlayer, 1, skt);
        this->sendAll(&size, 1, skt);
    }
}

void sendStart(const std::vector<StOperator> &playersInfo, const std::vector<EnemyDto> &enemiesInfo,
    const TypeGame& typeGame, const uint8_t& idMap, T *skt) {
    uint8_t event = START_CODE;
    this->sendAll(&event, 1, skt);
    
    sendPlayersInfo(playersInfo, skt);
    sendEnemiesInfo(enemiesInfo, skt);
    
    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    this->sendAll(&idGame, 1, skt);

    this->sendAll(&idMap, 1, skt);
}

void sendPlaying(const std::vector<StOperator> &playersInfo,
    const std::vector<EnemyDto> &enemiesInfo, T *skt) {
    uint8_t event = PLAYING_CODE;
    this->sendAll(&event, 1, skt);

    sendPlayersInfo(playersInfo, skt);
    sendEnemiesInfo(enemiesInfo, skt);
}


void sendOperator(const TypeOperator& typeOperator, T *skt) {
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

void sendOperator(const TypeInfected& typeInfected, T *skt) {
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

void sendState(const State& state, T *skt) {
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

void sendPlayersInfo(const std::vector<StOperator> &playersInfo, T *skt) {
    uint8_t playersCount = playersInfo.size();
    this->sendAll(&playersCount, 1, skt);
    for (auto it = playersInfo.begin(); it != playersInfo.end(); ++it) {
        uint8_t id = it->getId();
        this->sendAll(&id, 1, skt);
        sendOperator(it->getTypeOperator(), skt);
        sendState(it->getState(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
        uint8_t health = it->getHealth();
        this->sendAll(&health, 1, skt);
  }
}

void sendEnemiesInfo(const std::vector<EnemyDto> &enemiesInfo, T *skt) {
    uint8_t count = enemiesInfo.size();
    this->sendAll(&count, 1, skt);
    for (auto it = enemiesInfo.begin(); it != enemiesInfo.end(); ++it) {
        uint8_t id = it->getId();
        this->sendAll(&id, 1, skt);
        sendOperator(it->getTypeInfected(), skt);
        sendState(it->getState(), skt);
        sendPosition(it->getPosition().first, it->getPosition().second, skt); // x = it->second.first, y = it->second.second
  }   
}

void sendPosition(const uint16_t& x, const uint16_t& y, T *skt) {
    uint16_t xAux = htons(x);
    this->sendAll(&xAux, 2, skt);

    uint16_t yAux = htons(y);
    this->sendAll(&yAux, 2, skt);
}

    public:
        /*
        * Constructor que llama al constructor del padre
        * */
        explicit ServerProtocol() {}

        EventDTO getEvent(T *skt) {
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

        void sendSnapshot(
            const Snapshot &snapshot, T *skt) {
    Event event = snapshot.getEvent();
    if (event == Event::event_create) {
        sendCreate(snapshot.getCode(), snapshot.getIdPlayer(), skt);
    } else if (event == Event::event_join) {
        sendJoin(snapshot.getOk(), snapshot.getIdPlayer(), snapshot.getSize(), skt);
    } else if (event == Event::event_start_game) {
        sendStart(snapshot.getInfo(), snapshot.getEnemies(), snapshot.getTypeGame(),
            snapshot.getMap(), skt);
    } else {
        sendPlaying(snapshot.getInfo(), snapshot.getEnemies(), skt);
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