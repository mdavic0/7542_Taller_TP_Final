#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>
#include "Protocol.h"
#include "EventDTO.h"
#include "Snapshot.h"
#include <iostream>
/*
 * TDA ClientProtocol
 * Se comunica con el servidor a través de su T.
 */
template <typename T>
class ClientProtocol : public Protocol<T> {
    private:
 
void sendCreate(const std::string& scenario, const TypeOperator& typeOperator,
    const TypeGame& typeGame, const TypeDifficulty & typeDifficulty, std::shared_ptr<T> skt) {
    uint8_t command = CREATE_CODE;
    this->sendAll(&command, 1, skt);

    sendOperator(typeOperator, skt);

    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    this->sendAll(&idGame, 1, skt);

    sendDifficulty(typeDifficulty, skt);

    this->sendString(scenario, skt);
}

void sendJoin(const uint32_t& code, const TypeOperator& typeOperator, std::shared_ptr<T> skt) {
    uint8_t command = JOIN_CODE;
    this->sendAll(&command, 1, skt);

    sendOperator(typeOperator, skt);
    
    uint32_t codeAux = htonl(code);
    this->sendAll(&codeAux, 4, skt);
    
}

void sendStart(std::shared_ptr<T> skt) {
    uint8_t command = START_CODE;
    this->sendAll(&command, 1, skt);
}

void sendMove(const MoveTo& moveTo, const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = MOVE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);

    sendMoveTo(moveTo, skt);
}

void sendStopMove(const MoveTo& moveTo, const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = STOP_MOVE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);

    sendMoveTo(moveTo, skt);
}

void sendSmoke(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = THROW_SMOKE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendStopSmoke(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = STOP_SMOKE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendGrenade(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = THROW_GRENADE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendStopGrenade(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = STOP_GRENADE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendBlitz(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = BLITZ_ATACK_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendShoot(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = SHOOT_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendStopShoot(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = STOP_SHOOT_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendLeave(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = LEAVE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendRecharge(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = RECHARGE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendReanimate(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = REANIMATE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendStopReanimate(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = STOP_REANIMATE_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendCheatFinish(const uint8_t& idPlayer, std::shared_ptr<T> skt){
    uint8_t command = CHEAT_FINISH_GAME_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendCheatMunition(const uint8_t& idPlayer, std::shared_ptr<T> skt){
    uint8_t command = CHEAT_INFINITE_MUNITION_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendCheatVelocity(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = CHEAT_MORE_VELOCITY_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendCheatKills(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = CHEAT_KILL_ENEMIES_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendCheatHealth(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    uint8_t command = CHEAT_INFINITE_HEALTH_CODE;
    this->sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void sendOperator(const TypeOperator& typeOperator, std::shared_ptr<T> skt) {
    uint8_t op;
    if(typeOperator == TypeOperator::operator_idf){
        op = IDF_CODE;
    } else if (typeOperator == TypeOperator::operator_p90) {
        op = P90_CODE;
    } else if (typeOperator == TypeOperator::operator_scout) {
        op = SCOUT_CODE;
    }
    this->sendAll(&op, 1, skt);
}

void sendMoveTo(const MoveTo& moveTo, std::shared_ptr<T> skt) {
    uint8_t idDirection;
    if (moveTo == MoveTo::move_down) {
        idDirection = DOWN_CODE;
    } else if (moveTo == MoveTo::move_up) {
        idDirection = UP_CODE;
    } else if (moveTo == MoveTo::move_left) {
        idDirection = LEFT_CODE;
    } else if (moveTo == MoveTo::move_right) {
        idDirection = RIGHT_CODE;
    }
    this->sendAll(&idDirection, 1, skt);
}

void sendId(const uint8_t& idPlayer, std::shared_ptr<T> skt) {
    this->sendAll(&idPlayer, 1, skt);    
}

void sendDifficulty(const TypeDifficulty & typeDifficulty, std::shared_ptr<T> skt) {
    uint8_t diff;
    if(typeDifficulty == TypeDifficulty::difficulty_easy){
        diff = DIFFICULTY_EASY;
    } else if (typeDifficulty == TypeDifficulty::difficulty_normal) {
        diff = DIFFICULTY_NORMAL;
    } else if (typeDifficulty == TypeDifficulty::difficulty_hard) {
        diff = DIFFICULTY_HARD;
    } else if (typeDifficulty == TypeDifficulty::difficulty_god) {
        diff = DIFFICULTY_GOD;
    }
    this->sendAll(&diff, 1, skt);
}

Snapshot getCreate (std::shared_ptr<T> skt) {
    uint32_t code;
    this->recvAll(&code, 4, skt);
    code = ntohl(code);

    uint8_t idPlayer;
    this->recvAll(&idPlayer, 1, skt);

    return Snapshot(Event::event_create, code, idPlayer);
}

Snapshot getJoin (std::shared_ptr<T> skt) {
    uint8_t ok;
    this->recvAll(&ok, 1, skt);

    uint8_t idPlayer = 0;
    uint8_t size = 0;

    if (ok == 0) {
        this->recvAll(&idPlayer, 1, skt);
        this->recvAll(&size, 1, skt);
    }

    return Snapshot(Event::event_join, ok, idPlayer, size);
}

Snapshot getStart (std::shared_ptr<T> skt) {
    std::vector<StOperator> players = getPlayers(skt);
    std::vector<EnemyDto> enemies = getEnemies(skt);
    std::vector<ObstacleDto> obstacles = getObstacles(skt);    

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
    
    uint8_t idMap;
    this->recvAll(&idMap, 1, skt);

    // std::cout << "map " << (int)idMap << std::endl;
    return Snapshot(players, enemies, obstacles, game, idMap);
}

Snapshot getPlaying (std::shared_ptr<T> skt) {
    std::vector<StOperator> players = getPlayers(skt);
    std::vector<EnemyDto> enemies = getEnemies(skt);

    return Snapshot(players, enemies);
}

Snapshot getEnd(std::shared_ptr<T> skt) {
    return Snapshot(Event::event_end);
}

Snapshot getStats(std::shared_ptr<T> skt) {
    uint32_t time;
    this->recvAll(&time, 4, skt);
    time = ntohl(time);

    uint16_t shots;
    this->recvAll(&shots, 2, skt);
    shots = ntohs(shots);

    uint8_t kills;
    this->recvAll(&kills, 1, skt);

    return Snapshot(time, shots, kills);
}

std::vector<StOperator> getPlayers(std::shared_ptr<T> skt) {
    uint8_t playersCount;
    this->recvAll(&playersCount, 1, skt);

    std::vector<StOperator> vector;
    uint8_t idPlayer;

    uint8_t idOperator;
    TypeOperator type = TypeOperator::operator_idle;

    uint8_t idState;
    State state = State::idle;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < playersCount; i++) {
        this->recvAll(&idPlayer, 1, skt);

        this->recvAll(&idOperator, 1, skt);
        switch (idOperator) {
        case IDF_CODE:
            type = TypeOperator::operator_idf;
            break;
        
        case P90_CODE:
            type = TypeOperator::operator_p90;
            break;
        
        case SCOUT_CODE:
            type = TypeOperator::operator_scout;
            break;
        
        default:
            break;
        }

        this->recvAll(&idState, 1, skt);
        switch (idState) {
            case STATE_IDLE:
                state = State::idle;
                break;
            case STATE_MOVING:
                state = State::moving;
                break;
            case STATE_ATACK:
                state = State::atack;
                break;
            
            case STATE_INJURE:
                state = State::injure;
                break;

            case STATE_HABILITY:
                state = State::hability;
                break;

            case STATE_RECHARGE:
                state = State::recharge;
                break;
            
            default:
                break;
        }

        this->recvAll(&x, 2, skt);
        x = ntohs(x);
        this->recvAll(&y, 2, skt);
        y = ntohs(y);

        uint8_t health;
        this->recvAll(&health, 1, skt);

        uint8_t munition;
        this->recvAll(&munition, 1, skt);

        vector.push_back(StOperator(idPlayer, type, state, {x, y}, health, munition));
    }

    return vector;
}

std::vector<EnemyDto> getEnemies(std::shared_ptr<T> skt) {
    uint8_t count;
    this->recvAll(&count, 1, skt);

    std::vector<EnemyDto> vector;
    uint8_t id;

    uint8_t idType;
    TypeInfected type = TypeInfected::infected_zombie;

    uint8_t idState;
    State state = State::idle;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < count; i++) {
        this->recvAll(&id, 1, skt);

        this->recvAll(&idType, 1, skt);
        switch (idType) {

        case INFECTED_JUMPER:
            type = TypeInfected::infected_jumper;
            break;
        
        case INFECTED_WITCH:
            type = TypeInfected::infected_witch;
            break;
        
        case INFECTED_SPEAR:
            type = TypeInfected::infected_spear;
            break;
        
        case INFECTED_VENOM:
            type = TypeInfected::infected_venom;
            break;
        
        default:
            break;
        }

        this->recvAll(&idState, 1, skt);
        switch (idState) {
            case STATE_IDLE:
                state = State::idle;
                break;
            case STATE_MOVING:
                state = State::moving;
                break;
            case STATE_ATACK:
                state = State::atack;
                break;
            
            case STATE_INJURE:
                state = State::injure;
                break;

            case STATE_HABILITY:
                state = State::hability;
                break;

            case STATE_RECHARGE:
                state = State::recharge;
                break;
            
            default:
                break;
        }
        
        this->recvAll(&x, 2, skt);
        x = ntohs(x);
        this->recvAll(&y, 2, skt);
        y = ntohs(y);
        // std::cout << "x: " << x << " y: " << y << std::endl;

        vector.push_back(EnemyDto(id, type, state, {x, y}));
    }

    return vector;
}

std::vector<ObstacleDto> getObstacles(std::shared_ptr<T> skt) {
    uint8_t count;
    this->recvAll(&count, 1, skt);

    std::vector<ObstacleDto> vector;
    uint8_t id;

    uint8_t idType;
    TypeObstacle type = TypeObstacle::obstacle_tire;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < count; i++) {
        this->recvAll(&id, 1, skt);

        this->recvAll(&idType, 1, skt);
        switch (idType) {

        case OBSTACLE_TIRE:
            type = TypeObstacle::obstacle_tire;
            break;
        
        case OBSTACLE_CRATER:
            type = TypeObstacle::obstacle_crater;
            break;
        
        default:
            break;
        }

        this->recvAll(&x, 2, skt);
        x = ntohs(x);
        this->recvAll(&y, 2, skt);
        y = ntohs(y);

        vector.push_back(ObstacleDto(id, type, {x, y}));
    }

    return vector;
}

    public:
        /*
        * Constructor que llama al constructor del padre
        * */
        explicit ClientProtocol() {}

void sendEvent(const EventDTO& eventdto, std::shared_ptr<T> skt) {
    Event event = eventdto.getEvent();

    if (event == Event::event_create) {
        sendCreate(eventdto.getStr(), eventdto.getTypeOperator(), eventdto.getTypeGame(),
            eventdto.getTypeDifficulty(), skt);
    } else if (event == Event::event_join) {
        sendJoin(eventdto.getN(), eventdto.getTypeOperator(), skt);
    } else if (event == Event::event_start_game) {
        sendStart(skt);
    } else if (event == Event::event_move) {
        sendMove(eventdto.getMoveTo(), eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_stop_move) {
        sendStopMove(eventdto.getMoveTo(), eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_shoot) {
        sendShoot(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_stop_shoot) {
        sendStopShoot(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_throw_smoke) {
        sendSmoke(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_stop_smoke) {
        sendStopSmoke(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_throw_grenade) {
        sendGrenade(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_stop_grenade) {
        sendStopGrenade(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_blitz_atack) {
        sendBlitz(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_recharge) {
        sendRecharge(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_reanimate) {
        sendReanimate(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_stop_reanimate) {
        sendStopReanimate(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_leave) {
        sendLeave(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_cheat_finish_game) {
        sendCheatFinish(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_cheat_infinite_munition) {
        sendCheatMunition(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_cheat_more_velocity) {
        sendCheatVelocity(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_cheat_kill_enemies) {
        sendCheatKills(eventdto.getIdPlayer(), skt);
    } else if (event == Event::event_cheat_infinite_health) {
        sendCheatHealth(eventdto.getIdPlayer(), skt);
    }
};

Snapshot getSnapshot(std::shared_ptr<T> skt) {
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

    case PLAYING_CODE:
        return getPlaying(skt);
        break;

    case END_CODE:
        return getEnd(skt);
        break;

    case STATS_CODE:
        return getStats(skt);
        break;

    default:
        break;
    }
    return Snapshot(Event::event_invalid);
}

        /*
        * No queremos permitir que alguien haga copias
        * */
        ClientProtocol(const ClientProtocol&) = delete;
        ClientProtocol& operator=(const ClientProtocol&) = delete;

        /*
        * Queremos permitir mover a los objetos (move semantics).
        *
        * Como todos nuestros atributos son movibles, la implementación
        * por default de C++ nos alcanza.
        * */
        ClientProtocol(ClientProtocol&&) = default;
        ClientProtocol& operator=(ClientProtocol&&) = default;
};
#endif  // CLIENT_PROTOCOL_H_
