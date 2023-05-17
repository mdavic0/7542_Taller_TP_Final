#include "client_protocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>

ClientProtocol::ClientProtocol(MockSocket& skt) :
    skt(skt) {}

Snapshot ClientProtocol::create(const std::string& scenario) {
    uint8_t command = 0x01;
    sendAll(&command, 1);
    sendString(scenario);

    uint32_t code;
    recvAll(&code, 4);

    code = htonl(code);

    return std::move(Snapshot(Event::event_create, code, 0, ""));
}

Snapshot ClientProtocol::join(const uint32_t& code) {
    uint8_t command = 0x02;
    sendAll(&command, 1);

    uint32_t codeAux = htonl(code);
    sendAll(&codeAux, 4);

    uint8_t res;
    recvAll(&res, sizeof(res));

    return std::move(Snapshot(Event::event_join, ntohl(codeAux), res, ""));
}

Snapshot ClientProtocol::readMsg(const uint32_t& n) {
    uint8_t command;
    std::ostringstream msgs;
    uint32_t counter = 0;

    do {
        recvAll(&command, 1);
        if (counter < n-1) {
            msgs << recvString() << " ";
        } else {
            msgs << recvString();
        }
        counter++;
    } while (counter < n);

    std::string str(msgs.str());

    return std::move(Snapshot(Event::event_read, n, 0, str));
}

Snapshot ClientProtocol::sendMsg(const std::string& str) {
    uint8_t command = 0x03;
    sendAll(&command, 1);
    sendString(str);
    return std::move(Snapshot(Event::event_read, 0, 0, ""));
}

void ClientProtocol::sendAll(const void *data, unsigned int sz) {
    bool was_closed = false;
    int sokcet_ret = skt.sendall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        //throw LibError(errno, "Socket is closed and no byte was sent");
    }
}


void ClientProtocol::recvAll(void *data, unsigned int sz) {
    bool was_closed = false;
    bool sokcet_ret = skt.recvall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        //  throw LibError(errno, "Socket is closed in rev when receive a new byte is neccesary");
    }
}

void ClientProtocol::sendString(const std::string& str) {
    uint16_t len = htons(str.size());
    sendAll(&len, 2);
    sendAll(str.c_str(), str.size());
    return;
}

std::string ClientProtocol::recvString() {
    uint16_t len;
    recvAll(&len, 2);
    len = ntohs(len);

    std::vector<char> response(len+1);
    recvAll(response.data(), response.size()-1);
    response[len] = '\0';
    return std::string(response.data());
}

Snapshot ClientProtocol::sendEvent(const EventDTO& eventdto) {
    Event event = eventdto.getEvent();

    if (event == Event::event_create) {
        return std::move(create(eventdto.getStr()));
    } else if (event == Event::event_join) {
        return std::move(join(eventdto.getN()));
    } else if (event == Event::event_broadcast) {
        return std::move(sendMsg(eventdto.getStr()));
    } else if (event == Event::event_read) {
        return std::move(readMsg(eventdto.getN()));
    }
    return std::move(Snapshot(Event::event_invalid, 0, 0, ""));
}
