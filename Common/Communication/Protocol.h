#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <string>
#include <sstream>
#include <memory>
#include "Defines.h"
#include "Liberror.h"

/*
 * TDA Protocol
 * Métodos comunes cliente-servidor.
 */
template <typename T>
class Protocol{
    private:

    public:
        /*
        * Constructor para adquirir un T.
        * */
        explicit Protocol() {}

        /*
         * Método privado para enviar los bytes correspondientes
         * por medio del T.
         */
        void sendAll(
            const void *data,
            unsigned int sz,
            std::shared_ptr<T> skt) {
    bool was_closed = false;
    bool sokcet_ret = skt->sendall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        throw LibError(errno, "Socket is closed in rev when send a new byte is neccesary");
    }
}

        /*
         * Método privado para recibir los bytes correspondientes
         * por medio del T.
         */
        void recvAll(
            void *data,
            unsigned int sz,
            std::shared_ptr<T> skt) {
    bool was_closed = false;
    bool sokcet_ret = skt->recvall(data, sz, &was_closed);

    if (was_closed && sokcet_ret == 0) {
        throw LibError(errno, "Socket is closed in rev when receive a new byte is neccesary");
    }
}

         /*
          * Método privado para enviar strings por medio del T.
          */
        void sendString(const std::string& str,
            std::shared_ptr<T> skt) {
    uint16_t len = htons(str.size());
    sendAll(&len, 2, skt);
    sendAll(str.c_str(), str.size(), skt);
    return;
}


          /*
           * Método privado para recibir strings
           */
        std::string recvString(
            std::shared_ptr<T> skt) {
    uint16_t len;
    recvAll(&len, 2, skt);
    len = ntohs(len);

    std::vector<char> response(len+1);
    recvAll(response.data(), response.size()-1, skt);
    response[len] = '\0';
    return std::string(response.data());
}

    /*
    * No queremos permitir que alguien haga copias
    * */
        Protocol(const Protocol&) = delete;
        Protocol& operator=(const Protocol&) = delete;

        /*
        * Queremos permitir mover a los objetos (move semantics).
        *
        * Como todos nuestros atributos son movibles, la implementación
        * por default de C++ nos alcanza.
        * */
        Protocol(Protocol&&) = default;
        Protocol& operator=(Protocol&&) = default;
};
#endif  // COMMON_PROTOCOL_H_