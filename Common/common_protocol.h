#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <string>
#include <sstream>
#include "common_socket.h"
/*
 * TDA Protocol
 * Métodos comunes cliente-servidor.
 */
class Protocol{
    private:
        Socket skt;

    public:
        /*
        * Constructor para adquirir un socket.
        * */
        explicit Protocol(
            Socket&& skt);

        /*
         * Método privado para enviar los bytes correspondientes
         * por medio del socket.
         */
        void sendAll(
            const void *data,
            unsigned int sz);

        /*
         * Método privado para recibir los bytes correspondientes
         * por medio del socket.
         */
        void recvAll(
            void *data,
            unsigned int sz);

         /*
          * Método privado para enviar strings por medio del socket.
          */
        void sendString(const std::string& str);

          /*
           * Método privado para recibir strings
           */
        std::string recvString();

        void stop();
        
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