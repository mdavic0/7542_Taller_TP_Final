#include "ClientProtocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>

ClientProtocol::ClientProtocol(Socket&& skt) :
    Protocol(std::move(skt)) {}

void ClientProtocol::sendCreate(const std::string& scenario, const TypeOperator& typeOperator,
    const TypeGame& typeGame) {
    uint8_t command = CREATE_CODE;
    sendAll(&command, 1);

    sendOperator(typeOperator);

    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    sendAll(&idGame, 1);

    sendString(scenario);
}

void ClientProtocol::sendJoin(const uint32_t& code, const TypeOperator& typeOperator) {
    uint8_t command = JOIN_CODE;
    sendAll(&command, 1);

    sendOperator(typeOperator);
    
    uint32_t codeAux = htonl(code);
    sendAll(&codeAux, 4);
    
}

void ClientProtocol::sendStart() {
    uint8_t command = START_CODE;
    sendAll(&command, 1);
}

void ClientProtocol::sendMove(const MoveTo& moveTo, const uint8_t& idPlayer) {
    uint8_t command = MOVE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);

    sendMoveTo(moveTo);
}

void ClientProtocol::sendStopMove(const MoveTo& moveTo, const uint8_t& idPlayer) {
    uint8_t command = STOP_MOVE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);

    sendMoveTo(moveTo);
}

void ClientProtocol::sendSmoke(const uint8_t& idPlayer) {
    uint8_t command = THROW_SMOKE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendStopSmoke(const uint8_t& idPlayer) {
    uint8_t command = STOP_SMOKE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendGrenade(const uint8_t& idPlayer) {
    uint8_t command = THROW_GRENADE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendStopGrenade(const uint8_t& idPlayer) {
    uint8_t command = STOP_GRENADE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendBlitz(const uint8_t& idPlayer) {
    uint8_t command = BLITZ_ATACK_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendShoot(const uint8_t& idPlayer) {
    uint8_t command = SHOOT_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendStopShoot(const uint8_t& idPlayer) {
    uint8_t command = STOP_SHOOT_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendLeave(const uint8_t& idPlayer) {
    uint8_t command = LEAVE_CODE;
    sendAll(&command, 1);

    sendId(idPlayer);
}

void ClientProtocol::sendOperator(const TypeOperator& typeOperator) {
    uint8_t op;
    if(typeOperator == TypeOperator::operator_idf){
        op = IDF_CODE;
    } else if (typeOperator == TypeOperator::operator_p90) {
        op = P90_CODE;
    } else if (typeOperator == TypeOperator::operator_scout) {
        op = SCOUT_CODE;
    }
    sendAll(&op, 1);
}

void ClientProtocol::sendMoveTo(const MoveTo& moveTo) {
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
    sendAll(&idDirection, 1);
}

void ClientProtocol::sendId(const uint8_t& idPlayer) {
    sendAll(&idPlayer, 1);    
}

Snapshot ClientProtocol::getCreate () {
    uint32_t code;
    recvAll(&code, 4);
    code = ntohl(code);

    uint8_t idPlayer;
    recvAll(&idPlayer, 1);

    return Snapshot(Event::event_create, code, idPlayer);
}

Snapshot ClientProtocol::getJoin () {
    uint8_t ok;
    recvAll(&ok, 1);

    uint8_t idPlayer = 0;
    uint8_t size = 0;

    if (ok == 0) {
        recvAll(&idPlayer, 1);
        recvAll(&size, 1);
    }

    return Snapshot(Event::event_join, ok, idPlayer, size);
}

Snapshot ClientProtocol::getStart () {
    std::vector<StOperator> players = getPlayers();
    std::vector<EnemyDto> enemies = getEnemies();
    
    uint8_t idGame;
    recvAll(&idGame, 1);
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
    recvAll(&idMap, 1);
    return Snapshot(players, enemies, game, idMap);
}

Snapshot ClientProtocol::getPlaying () {
    return Snapshot(getPlayers(), getEnemies());
}

std::vector<StOperator> ClientProtocol::getPlayers() {
    uint8_t playersCount;
    recvAll(&playersCount, 1);

    std::vector<StOperator> vector;
    uint8_t idPlayer;

    uint8_t idOperator;
    TypeOperator type = TypeOperator::operator_idle;

    uint8_t idState;
    State state = State::idle;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < playersCount; i++) {
        recvAll(&idPlayer, 1);

        recvAll(&idOperator, 1);
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

        recvAll(&idState, 1);
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

        recvAll(&x, 2);
        x = ntohs(x);
        // std::cout << "X " << (int)x << std::endl;
        recvAll(&y, 2);
        y = ntohs(y);
        // std::cout << "Y " << (int)y << std::endl;

        uint8_t health;
        recvAll(&health, 1);
        vector.push_back(StOperator(idPlayer, type, state, {x, y}, health));
    }

    return vector;
}

std::vector<EnemyDto> ClientProtocol::getEnemies() {
    uint8_t count;
    recvAll(&count, 1);

    std::vector<EnemyDto> vector;
    uint8_t id;

    uint8_t idType;
    TypeInfected type = TypeInfected::infected_zombie;

    uint8_t idState;
    State state = State::idle;

    int16_t x;
    int16_t y;

    for (uint8_t i = 0; i < count; i++) {
        recvAll(&id, 1);

        recvAll(&idType, 1);
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

        recvAll(&idState, 1);
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
        
        recvAll(&x, 2);
        x = ntohs(x);
        // std::cout << "X " << (int)x << std::endl;
        recvAll(&y, 2);
        y = ntohs(y);
        // std::cout << "Y " << (int)y << std::endl;

        vector.push_back(EnemyDto(id, type, state, {x, y}));
    }

    return vector;
}

void ClientProtocol::sendEvent(const EventDTO& eventdto) {
    Event event = eventdto.getEvent();

    if (event == Event::event_create) {
        sendCreate(eventdto.getStr(), eventdto.getTypeOperator(), eventdto.getTypeGame());
    } else if (event == Event::event_join) {
        sendJoin(eventdto.getN(), eventdto.getTypeOperator());
    } else if (event == Event::event_start_game) {
        sendStart();
    } else if (event == Event::event_move) {
        sendMove(eventdto.getMoveTo(), eventdto.getIdPlayer());
    } else if (event == Event::event_stop_move) {
        sendStopMove(eventdto.getMoveTo(), eventdto.getIdPlayer());
    } else if (event == Event::event_shoot) {
        sendShoot(eventdto.getIdPlayer());
    } else if (event == Event::event_stop_shoot) {
        sendStopShoot(eventdto.getIdPlayer());
    } else if (event == Event::event_throw_smoke) {
        sendSmoke(eventdto.getIdPlayer());
    } else if (event == Event::event_stop_smoke) {
        sendStopSmoke(eventdto.getIdPlayer());
    } else if (event == Event::event_throw_grenade) {
        sendGrenade(eventdto.getIdPlayer());
    } else if (event == Event::event_stop_grenade) {
        sendStopGrenade(eventdto.getIdPlayer());
    } else if (event == Event::event_blitz_atack) {
        sendBlitz(eventdto.getIdPlayer());
    } else if (event == Event::event_leave) {
        sendLeave(eventdto.getIdPlayer());
    }
    
}

Snapshot ClientProtocol::getSnapshot() {
    uint8_t event;
    recvAll(&event, 1);

    switch (event) {
    case CREATE_CODE:
        return getCreate();
        break;

    case JOIN_CODE:
        return getJoin();
        break;

    case START_CODE:
        return getStart();
        break;

    case PLAYING_CODE:
        return getPlaying();
        break;

    default:
        break;
    }
    return Snapshot(Event::event_invalid, (uint8_t)0, 0, 0);
}
