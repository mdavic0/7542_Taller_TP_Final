/*#include "Protocol.h"
#include "Liberror.h"
#include <arpa/inet.h>
#include <vector>
#include <utility>
#include <iostream>

Protocol::Protocol() {}

void Protocol::sendAll(const void *data, unsigned int sz, T *skt) {
    bool was_closed = false;
    bool sokcet_ret = skt->sendall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        throw LibError(errno, "T is closed in rev when send a new byte is neccesary");
    }
}

void Protocol::recvAll(void *data, unsigned int sz, T *skt) {
    bool was_closed = false;
    bool sokcet_ret = skt->recvall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        throw LibError(errno, "T is closed in rev when receive a new byte is neccesary");
    }
}

void Protocol::sendString(const std::string& str, T *skt) {
    uint16_t len = htons(str.size());
    sendAll(&len, 2, skt);
    sendAll(str.c_str(), str.size(), skt);
    return;
}

std::string Protocol::recvString(T *skt) {
    uint16_t len;
    recvAll(&len, 2, skt);
    len = ntohs(len);

    std::vector<char> response(len+1);
    recvAll(response.data(), response.size()-1, skt);
    response[len] = '\0';
    return std::string(response.data());
}

void Protocol::stop() {
    //skt.shutdown(2);
    //skt.close();
}
*/