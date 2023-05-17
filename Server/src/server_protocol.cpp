#include "server_protocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>

ServerProtocol::ServerProtocol(MockSocket& skt) : peer(skt) { }

EventDTO ServerProtocol::getCreate() {
    return std::move(EventDTO(Event::event_create, recvString(), 0));
}

EventDTO ServerProtocol::getJoin() {
    uint32_t code;
    recvAll(&code, 4);
    code = ntohl(code);

    return std::move(EventDTO(Event::event_join, "", code));
}

EventDTO ServerProtocol::getBroadcast() {
    return std::move(EventDTO(Event::event_broadcast, recvString(), 0));
}

void ServerProtocol::responseCreate(uint32_t code) {
    code = htonl(code);
    sendAll(&code, 4);
}

void ServerProtocol::responseJoin(uint8_t ok) {
    sendAll(&ok, 1);
}

void ServerProtocol::responseBroadcast(const std::string& str) {
    uint8_t event = 0x04;
    sendAll(&event, 1);
    sendString(str);
}

void ServerProtocol::sendAll(const void *data, unsigned int sz) {
    bool was_closed = false;
    int sokcet_ret = peer.sendall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        //throw LibError(errno, "Socket is closed and no byte was sent");
    }
}

void ServerProtocol::recvAll(void *data, unsigned int sz) {
    bool was_closed = false;
    bool sokcet_ret = peer.recvall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        //throw LibError(errno, "Socket is closed in rev when receive a new byte is neccesary");
    }
}

void ServerProtocol::sendString(const std::string& str) {
    uint16_t len = htons(str.size());
    sendAll(&len, 2);
    sendAll(str.c_str(), str.size());
    return;
}

std::string ServerProtocol::recvString() {
    uint16_t len;
    recvAll(&len, 2);
    len = ntohs(len);

    std::vector<char> response(len+1);
    recvAll(response.data(), response.size()-1);
    response[len] = '\0';
    return std::string(response.data());
}

EventDTO ServerProtocol::getEvent() {
    bool was_closed = false;

    int8_t buf[1];
    int sokcet_ret = peer.recvall(buf, sizeof(buf), &was_closed);

    // Se cierra el socket y no se lee ningun byte
    if (was_closed && sokcet_ret == 0) {
        return std::move(EventDTO(Event::event_leave, "", 0));
    }

    if (*buf == 0x01) {
        return std::move(getCreate());
    } else if (*buf == 0x02) {
        return std::move(getJoin());
    } else if (*buf == 0x03) {
        return std::move(getBroadcast());
    }

    return std::move(EventDTO(Event::event_invalid, "", 0));
}

void ServerProtocol::sendSnapshot(const Snapshot &snapshot) {
    Event event = snapshot.getEvent();

    if (event == Event::event_create) {
        responseCreate(snapshot.getCode());
    } else if (event == Event::event_join) {
        responseJoin(snapshot.getOk());
    } else if (event == Event::event_broadcast) {
        responseBroadcast(snapshot.getStr());
    }
}

void ServerProtocol::stop() {
    //peer.shutdown(2);
    //peer.close();
}