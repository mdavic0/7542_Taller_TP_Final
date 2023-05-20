#include "server_protocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>

ServerProtocol::ServerProtocol(Socket&& skt) : Protocol(std::move(skt)) { }

EventDTO ServerProtocol::getCreate() {
    return EventDTO(Event::event_create, MoveTo::move_not, recvString(), 0);
}

EventDTO ServerProtocol::getJoin() {
    uint32_t code;
    recvAll(&code, 4);
    code = ntohl(code);
  
    return EventDTO(Event::event_join, MoveTo::move_idle, "", code);

}

EventDTO ServerProtocol::getMove() {
    return EventDTO(Event::event_move, MoveTo::move_right, "", 0);
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

void ServerProtocol::sendMove() {
    uint8_t event = 0x03;
    sendAll(&event, 1);
}

EventDTO ServerProtocol::getEvent() {
    uint8_t event;
    recvAll(&event, 1);


    if (event == 0x01) {
        return getCreate();
    } else if (event == 0x02) {
        return getJoin();
    } else if (event == 0x03) {
        return getMove();
    }

    return EventDTO(Event::event_invalid, MoveTo::move_idle, "", 0);
}

void ServerProtocol::sendSnapshot(const Snapshot &snapshot) {
    Event event = snapshot.getEvent();

    if (event == Event::event_create) {
        sendCreate(snapshot.getCode());
    } else if (event == Event::event_join) {
        sendJoin(snapshot.getOk());
    } else if (event == Event::event_move) {
        sendMove();
    }
}

void ServerProtocol::stop() {
    Protocol::stop();
}