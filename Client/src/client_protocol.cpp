#include "client_protocol.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>
#include "common_liberror.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname) :
    skt(hostname.c_str(), servname.c_str()) {}

ResponseDTO ClientProtocol::create(const std::string& scenario) {
    uint8_t command = 0x01;
    sendAll(&command, 1);
    sendString(scenario);

    uint32_t code;
    recvAll(&code, 4);

    code = htonl(code);

    return std::move(ResponseDTO(Command::command_create, code, 0, ""));
}

ResponseDTO ClientProtocol::join(const uint32_t& code) {
    uint8_t command = 0x02;
    sendAll(&command, 1);

    uint32_t codeAux = htonl(code);
    sendAll(&codeAux, 4);

    uint8_t res;
    recvAll(&res, sizeof(res));

    return std::move(ResponseDTO(Command::command_join, ntohl(codeAux), res, ""));
}

ResponseDTO ClientProtocol::readMsg(const uint32_t& n) {
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

    return std::move(ResponseDTO(Command::command_read, n, 0, str));
}

ResponseDTO ClientProtocol::sendMsg(const std::string& str) {
    uint8_t command = 0x03;
    sendAll(&command, 1);
    sendString(str);
    return std::move(ResponseDTO(Command::command_read, 0, 0, ""));
}

void ClientProtocol::sendAll(const void *data, unsigned int sz) {
    bool was_closed = false;
    int sokcet_ret = skt.sendall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        throw LibError(errno, "Socket is closed and no byte was sent");
    }
}


void ClientProtocol::recvAll(void *data, unsigned int sz) {
    bool was_closed = false;
    bool sokcet_ret = skt.recvall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        throw LibError(errno, "Socket is closed in rev when receive a new byte is neccesary");
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

ResponseDTO ClientProtocol::sendCommand(const CommandDTO& commanddto) {
    Command command = commanddto.getCommand();

    if (command == Command::command_create) {
        return std::move(create(commanddto.getStr()));
    } else if (command == Command::command_join) {
        return std::move(join(commanddto.getN()));
    } else if (command == Command::command_broadcast) {
        return std::move(sendMsg(commanddto.getStr()));
    } else if (command == Command::command_read) {
        return std::move(readMsg(commanddto.getN()));
    }
    return std::move(ResponseDTO(Command::command_invalid, 0, 0, ""));
}

