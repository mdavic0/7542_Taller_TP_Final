#include "ServerProtocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>

ServerProtocol::ServerProtocol(Socket&& skt) : Protocol(std::move(skt)) { }

EventDTO ServerProtocol::getCreate() {
    uint8_t idOperator;
    recvAll(&idOperator, 1);
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

    return EventDTO(recvString(), game, op);
}

EventDTO ServerProtocol::getJoin() {
    uint8_t idOperator;
    recvAll(&idOperator, 1);
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
    recvAll(&code, 4);
    code = ntohl(code);
  
    return EventDTO(code, op);

}

EventDTO ServerProtocol::getMove() {
    uint8_t id;
    recvAll(&id, 1);

    uint8_t direction;
    recvAll(&direction, 1);
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

EventDTO ServerProtocol::getStopMove() {
    uint8_t id;
    recvAll(&id, 1);

    uint8_t direction;
    recvAll(&direction, 1);
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

EventDTO ServerProtocol::getStart() {
    return EventDTO(Event::event_start_game, MoveTo::move_idle, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
}

void ServerProtocol::sendCreate(const uint32_t& code, const uint8_t& idPlayer) {
    uint8_t event = 0x01;
    sendAll(&event, 1);

    uint32_t aux = htonl(code);
    sendAll(&aux, 4);

    sendAll(&idPlayer, 1);
}

void ServerProtocol::sendJoin(const uint8_t& ok, const uint8_t& idPlayer) {
    uint8_t event = 0x02;
    sendAll(&event, 1);

    sendAll(&ok, 1);

    if (ok == 0) {
        sendAll(&idPlayer, 1);
    }
}

void ServerProtocol::sendPlaying(const std::map<uint8_t, StOperator> &playersInfo) {
    uint8_t event = 0x05;
    sendAll(&event, 1);
    uint8_t playersCount = playersInfo.size();
    sendAll(&playersCount, 1);
    for (auto it = playersInfo.begin(); it != playersInfo.end(); ++it) {
        sendAll(&it->first, 1);
        sendOperator(it->second.getTypeOperator());
        sendState(it->second.getState());
        sendPosition(it->second.getPosition().first, it->second.getPosition().second); // x = it->second.first, y = it->second.second
  }
}


void ServerProtocol::sendOperator(const TypeOperator& typeOperator) {
    if(typeOperator == TypeOperator::operator_idf){
        uint8_t op = IDF_CODE;
        sendAll(&op, 1);
    } else if (typeOperator == TypeOperator::operator_p90) {
        uint8_t op = P90_CODE;
        sendAll(&op, 1);
    } else if (typeOperator == TypeOperator::operator_scout) {
        uint8_t op = SCOUT_CODE;
        sendAll(&op, 1);        
    }
}

void ServerProtocol::sendState(const State& state) {
    if(state == State::idle){
        uint8_t aux = STATE_IDLE;
        sendAll(&aux, 1);
    } else if (state == State::moving) {
        uint8_t aux = STATE_MOVING;
        sendAll(&aux, 1);
    } else if (state == State::atack) {
        uint8_t aux = STATE_ATACK;
        sendAll(&aux, 1);       
    } else if (state == State::injure) {
        uint8_t aux = STATE_INJURE;
        sendAll(&aux, 1);       
    } else if (state == State::hability) {
        uint8_t aux = STATE_HABILITY;
        sendAll(&aux, 1);       
    }
}

void ServerProtocol::sendPosition(const uint16_t& x, const uint16_t& y) {
    uint16_t xAux = htons(x);
    sendAll(&xAux, 2);

    uint16_t yAux = htons(y);
    sendAll(&yAux, 2);
}

EventDTO ServerProtocol::getEvent() {
    uint8_t event;
    recvAll(&event, 1);

    switch (event) {
    case CREATE_CODE:
        return getCreate();
        break;
    
    case JOIN_CODE:
        return getJoin();
        break;
        
    case MOVE_CODE:
        return getMove();
        break;
        
    case STOP_MOVE_CODE:
        return getStopMove();
        break;

    case START_CODE:
        return getStart();
        break;

    default:
        break;
    }

    return EventDTO(Event::event_invalid, MoveTo::move_idle, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
}

void ServerProtocol::sendSnapshot(const Snapshot &snapshot) {
    Event event = snapshot.getEvent();
    if (event == Event::event_create) {
        sendCreate(snapshot.getCode(), snapshot.getIdPlayer());
    } else if (event == Event::event_join) {
        sendJoin(snapshot.getOk(), snapshot.getIdPlayer());
    } else {
        sendPlaying(snapshot.getInfo());
    }
}

void ServerProtocol::stop() {
    Protocol::stop();
}
