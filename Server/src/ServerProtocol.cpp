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

    return EventDTO(Event::event_create, MoveTo::move_idle, op, game, recvString(), 0);
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
  
    return EventDTO(Event::event_join, MoveTo::move_idle, op, TypeGame::game_idle, "", code);

}

EventDTO ServerProtocol::getMove() {
    uint8_t direction;
    recvAll(&direction, 1);

    switch (direction) {
    case UP_CODE:
        return EventDTO(Event::event_move, MoveTo::move_up, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
        break;
    
    case DOWN_CODE:
        return EventDTO(Event::event_move, MoveTo::move_down, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
        break;
        
    case RIGHT_CODE:
        return EventDTO(Event::event_move, MoveTo::move_right, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
        break;
        
    case LEFT_CODE:
        return EventDTO(Event::event_move, MoveTo::move_left, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
        break;

    default:
        break;
    }

    return EventDTO(Event::event_invalid, MoveTo::move_idle, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
}

EventDTO ServerProtocol::getStopMove() {
    return EventDTO(Event::event_stop_move, MoveTo::move_idle, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
}
EventDTO ServerProtocol::getStart() {
    return EventDTO(Event::event_start_game, MoveTo::move_idle, TypeOperator::operator_idle, TypeGame::game_idle, "", 0);
}

void ServerProtocol::sendCreate(uint32_t code) {
    uint8_t event = 0x01;
    sendAll(&event, 1);

    code = htonl(code);
    sendAll(&code, 4);
}

void ServerProtocol::sendJoin(uint8_t ok) {
    uint8_t event = 0x02;
    sendAll(&event, 1);

    sendAll(&ok, 1);
}

void ServerProtocol::sendPlaying(std::map<TypeOperator, std::pair<uint16_t, uint16_t>> &playersInfo) {
    for (auto it = playersInfo.begin(); it != playersInfo.end(); ++it) {
        sendOperator(it->first);
        sendPosition(std::get<0>(it->second), std::get<1>(it->second));
  }
}


void ServerProtocol::sendOperator(TypeOperator typeOperator) {
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
    // TODO: En realidad el snapshot se crea una vez que pasaron 0 o muchos eventos,
    //       es como una foto del momento, no se si hay que separar los sends,
    //       por que los eventos se procesan del lado del sv, los que si hay que distinguir
    //       es create y join seguro
    if (event == Event::event_create) {
        sendCreate(snapshot.getCode());
    } else if (event == Event::event_join) {
        sendJoin(snapshot.getOk());
    } else {
        std::map<TypeOperator, std::pair<uint16_t, uint16_t>> pos = snapshot.getPositions();
        sendPlaying(pos);
    }
}

void ServerProtocol::stop() {
    Protocol::stop();
}