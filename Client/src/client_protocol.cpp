#include "client_protocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>

ClientProtocol::ClientProtocol(Socket&& skt) :
    Protocol(std::move(skt)) {}

void ClientProtocol::sendCreate(const std::string& scenario, TypeOperator typeOperator,
            TypeGame typeGame) {
    uint8_t command = 0x01;
    sendAll(&command, 1);

    uint8_t idOperator;
    if (typeOperator == TypeOperator::operator_idf) {
        idOperator = IDF_CODE;
    } else if (typeOperator == TypeOperator::operator_p90) {
        idOperator = P90_CODE;
    } else if (typeOperator == TypeOperator::operator_scout) {
        idOperator = SCOUT_CODE;
    }
    sendAll(&idOperator, 1);

    uint8_t idGame;
    if (typeGame == TypeGame::game_survival) {
        idGame = SURVIVAL_CODE;
    } else if (typeGame == TypeGame::game_clear_zone) {
        idGame = CLEAR_ZONE_CODE;
    }
    sendAll(&idGame, 1);

    sendString(scenario);
}

void ClientProtocol::sendJoin(const uint32_t& code, TypeOperator typeOperator) {
    uint8_t command = 0x02;
    sendAll(&command, 1);

    uint8_t idOperator;
    if (typeOperator == TypeOperator::operator_idf) {
        idOperator = IDF_CODE;
    } else if (typeOperator == TypeOperator::operator_p90) {
        idOperator = P90_CODE;
    } else if (typeOperator == TypeOperator::operator_scout) {
        idOperator = SCOUT_CODE;
    }
    sendAll(&idOperator, 1);
    
    uint32_t codeAux = htonl(code);
    sendAll(&codeAux, 4);
    
}

void ClientProtocol::sendMove (MoveTo moveTo) {
    uint8_t command = 0x03;
    sendAll(&command, 1);

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

void ClientProtocol::sendStopMove () {
    uint8_t command = 0x04;
    sendAll(&command, 1);
}

Snapshot ClientProtocol::getCreate () {
    uint32_t code;
    recvAll(&code, 4);
    code = ntohl(code);

    return Snapshot(Event::event_create, TypeOperator::operator_idle, code, 0);
}

Snapshot ClientProtocol::getJoin () {
    uint8_t ok;
    recvAll(&ok, 1);

    return Snapshot(Event::event_join, TypeOperator::operator_idle, 0, ok);
}

Snapshot ClientProtocol::getPlaying () {
    std::map<TypeOperator, std::pair<uint16_t, uint16_t>> map;

    uint8_t idOperator;
    TypeOperator type = TypeOperator::operator_idle;
    uint16_t x;
    uint16_t y;
    for (uint8_t i = 0; i < 3; i++) {
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

        recvAll(&x, 2);
        x = ntohs(x);
        
        recvAll(&y, 2);
        y = ntohs(y);

        map.insert({type, {x, y}});
    }

    return Snapshot(map, Event(5));
}

void ClientProtocol::sendEvent(const EventDTO& eventdto) {
    Event event = eventdto.getEvent();

    if (event == Event::event_create) {
        sendCreate(eventdto.getStr(), eventdto.getTypeOperator(), eventdto.getTypeGame());
    } else if (event == Event::event_join) {
        sendJoin(eventdto.getN(), eventdto.getTypeOperator());
    } else if (event == Event::event_move) {
        sendMove(eventdto.getMoveTo());
    } else if (event == Event::event_stop_move) {
        sendStopMove();
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

    case PLAYING_CODE:
        return getPlaying();
        break;

    case START_CODE:
        return getPlaying();
        break;

    default:
        break;
    }
    return Snapshot(Event::event_invalid, TypeOperator::operator_idle, 0, 0);
}
