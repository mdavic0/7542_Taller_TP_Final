#include "client_protocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>

ClientProtocol::ClientProtocol(Socket&& skt) :
    Protocol(std::move(skt)) {}

void ClientProtocol::sendCreate(const std::string& scenario) {
    uint8_t command = 0x01;
    sendAll(&command, 1);
    sendString(scenario);
}

void ClientProtocol::sendJoin(const uint32_t& code) {
    uint8_t command = 0x02;
    sendAll(&command, 1);

    uint32_t codeAux = htonl(code);
    sendAll(&codeAux, 4);
}

void ClientProtocol::sendMove () {
    uint8_t command = 0x03;
    sendAll(&command, 1);

}

Snapshot ClientProtocol::getCreate () {
    uint32_t code;
    recvAll(&code, 4);

    code = htonl(code);

    return Snapshot(Event::event_create, code, 0, "");
}

Snapshot ClientProtocol::getJoin () {
    uint8_t res;
    recvAll(&res, sizeof(res));

    return Snapshot(Event::event_join, 0, res, "");
}

Snapshot ClientProtocol::getMove () {
    return Snapshot(Event::event_move, 0, 0, "");
}

void ClientProtocol::sendEvent(const EventDTO& eventdto) {
    Event event = eventdto.getEvent();

    if (event == Event::event_create) {
        sendCreate(eventdto.getStr());
    } else if (event == Event::event_join) {
        sendJoin(eventdto.getN());
    } else if (event == Event::event_move) {
        sendMove();
    }
    
}

Snapshot ClientProtocol::getSnapshot() {
    uint8_t event;
    recvAll(&event, 1);

    if (event == 0x01) {
        return getCreate();
    } else if (event == 0x02) {
        return getJoin();
    } else if (event == 0x03) {
        return getMove();
    }
    return Snapshot(Event::event_invalid, 0, 0, "");
}
