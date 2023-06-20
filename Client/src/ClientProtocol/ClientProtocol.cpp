/*#include "ClientProtocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>

ClientProtocol::ClientProtocol() {}

void ClientProtocol::sendCreate(const std::string& scenario, const TypeOperator& typeOperator,
    const TypeGame& typeGame, Socket *skt) {
    uint8_t command = CREATE_CODE;
    sendAll(&command, 1, skt);

    sendOperator(typeOperator, skt);

    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    sendAll(&idGame, 1, skt);

    sendString(scenario, skt);
}

void ClientProtocol::sendJoin(const uint32_t& code, const TypeOperator& typeOperator, Socket *skt) {
    uint8_t command = JOIN_CODE;
    sendAll(&command, 1, skt);

    sendOperator(typeOperator, skt);
    
    uint32_t codeAux = htonl(code);
    sendAll(&codeAux, 4, skt);
    
}

void ClientProtocol::sendStart(Socket *skt) {
    uint8_t command = START_CODE;
    sendAll(&command, 1, skt);
}

void ClientProtocol::sendMove(const MoveTo& moveTo, const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = MOVE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);

    sendMoveTo(moveTo, skt);
}

void ClientProtocol::sendStopMove(const MoveTo& moveTo, const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = STOP_MOVE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);

    sendMoveTo(moveTo, skt);
}

void ClientProtocol::sendSmoke(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = THROW_SMOKE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendStopSmoke(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = STOP_SMOKE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendGrenade(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = THROW_GRENADE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendStopGrenade(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = STOP_GRENADE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendBlitz(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = BLITZ_ATACK_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendShoot(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = SHOOT_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendStopShoot(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = STOP_SHOOT_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendLeave(const uint8_t& idPlayer, Socket *skt) {
    uint8_t command = LEAVE_CODE;
    sendAll(&command, 1, skt);

    sendId(idPlayer, skt);
}

void ClientProtocol::sendOperator(const TypeOperator& typeOperator, Socket *skt) {
    uint8_t op;
    if(typeOperator == TypeOperator::operator_idf){
        op = IDF_CODE;
    } else if (typeOperator == TypeOperator::operator_p90) {
        op = P90_CODE;
    } else if (typeOperator == TypeOperator::operator_scout) {
        op = SCOUT_CODE;
    }
    sendAll(&op, 1, skt);
}

void ClientProtocol::sendMoveTo(const MoveTo& moveTo, Socket *skt) {
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
    sendAll(&idDirection, 1, skt);
}

void ClientProtocol::sendId(const uint8_t& idPlayer, Socket *skt) {
    sendAll(&idPlayer, 1, skt);    
}

Snapshot ClientProtocol::getCreate (Socket *skt) {
    uint32_t code;
    recvAll(&code, 4, skt);
    code = ntohl(code);

    uint8_t idPlayer;
    recvAll(&idPlayer, 1, skt);

    return Snapshot(Event::event_create, code, idPlayer);
}

Snapshot ClientProtocol::getJoin (Socket *skt) {
    uint8_t ok;
    recvAll(&ok, 1, skt);

    uint8_t idPlayer = 0;
    uint8_t size = 0;

    if (ok == 0) {
        recvAll(&idPlayer, 1, skt);
        recvAll(&size, 1, skt);
    }

    return Snapshot(Event::event_join, ok, idPlayer, size);
}

Snapshot ClientProtocol::getStart (Socket *skt) {
    std::vector<StOperator> players = getPlayers();
    std::vector<EnemyDto> enemies = getEnemies();
    std::vector<ObstacleDto> obstacles = getObstacles();    

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
    
    uint8_t idMap;
    recvAll(&idMap, 1, skt);
    return Snapshot(players, enemies, obstacles, game, idMap);
}

Snapshot ClientProtocol::getPlaying (Socket *skt) {
    std::vector<StOperator> players = getPlayers(skt);
    std::vector<EnemyDto> enemies = getEnemies(skt);

    return Snapshot(players, enemies);
}

Snapshot ClientProtocol::getEnd(Socket *skt) {
    return Snapshot(Event::event_end);
}

Snapshot ClientProtocol::getStats(Socket *skt) {
    uint32_t time;
    recvAll(&time, 4, skt);
    time = ntohl(time);

    uint16_t shots;
    recvAll(&shots, 2, skt);
    shots = ntohs(shots);

    uint8_t kills;
    recvAll(&kills, 1, skt);

    return Snapshot(time, shots, kills);
}

std::vector<StOperator> ClientProtocol::getPlayers(Socket *skt) {
    uint8_t playersCount;
    recvAll(&playersCount, 1, skt);

    std::vector<StOperator> vector;
    uint8_t idPlayer;

    uint8_t idOperator;
    TypeOperator type = TypeOperator::operator_idle;

    uint8_t idState;
    State state = State::idle;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < playersCount; i++) {
        recvAll(&idPlayer, 1, skt);

        recvAll(&idOperator, 1, skt);
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

        recvAll(&idState, 1, skt);
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

        recvAll(&x, 2, skt);
        x = ntohs(x);
        // std::cout << "X " << (int)x << std::endl;
        recvAll(&y, 2, skt);
        y = ntohs(y);
        // std::cout << "Y " << (int)y << std::endl;

        uint8_t health;
        recvAll(&health, 1, skt);

        uint8_t munition;
        recvAll(&munition, 1, skt);

        vector.push_back(StOperator(idPlayer, type, state, {x, y}, health, munition));

    }

    return vector;
}

std::vector<EnemyDto> ClientProtocol::getEnemies(Socket *skt) {
    uint8_t count;
    recvAll(&count, 1, skt);

    std::vector<EnemyDto> vector;
    uint8_t id;

    uint8_t idType;
    TypeInfected type = TypeInfected::infected_zombie;

    uint8_t idState;
    State state = State::idle;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < count; i++) {
        recvAll(&id, 1, skt);

        recvAll(&idType, 1, skt);
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

        recvAll(&idState, 1, skt);
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
        
        recvAll(&x, 2, skt);
        x = ntohs(x);
        // std::cout << "X " << (int)x << std::endl;
        recvAll(&y, 2, skt);
        y = ntohs(y);
        // std::cout << "Y " << (int)y << std::endl;

        vector.push_back(EnemyDto(id, type, state, {x, y}));
    }

    return vector;
}

std::vector<ObstacleDto> ClientProtocol::getObstacles(Socket *skt) {
    uint8_t count;
    recvAll(&count, 1, skt);

    std::vector<ObstacleDto> vector;
    uint8_t id;

    uint8_t idType;
    TypeObstacle type = TypeObstacle::obstacle_tire;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < count; i++) {
        recvAll(&id, 1, skt);

        recvAll(&idType, 1, skt);
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

        recvAll(&x, 2, skt);
        x = ntohs(x);
        // std::cout << "X " << (int)x << std::endl;
        recvAll(&y, 2, skt);
        y = ntohs(y);
        // std::cout << "Y " << (int)y << std::endl;
        std::cout << "x: " << x << " y: " << y << std::endl; 
        vector.push_back(ObstacleDto(id, type, {x, y}));
    }

    return vector;
}

void ClientProtocol::sendEvent(const EventDTO& eventdto, Socket *skt) {
    Event event = eventdto.getEvent();

    if (event == Event::event_create) {
        sendCreate(eventdto.getStr(), eventdto.getTypeOperator(), eventdto.getTypeGame(), skt);
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
    } else if (event == Event::event_leave) {
        sendLeave(eventdto.getIdPlayer(), skt);
    }
    
}

Snapshot ClientProtocol::getSnapshot(Socket *skt) {
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

    case PLAYING_CODE:
        return getPlaying(skt);
        break;

    case END_CODE:
        return getEnd();
        break;

    case STATS_CODE:
        return getStats();
        break;

    default:
        break;
    }
    return Snapshot(Event::event_invalid);
}
*/