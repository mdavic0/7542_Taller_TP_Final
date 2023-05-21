#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <string>
#include <sstream>
#include "common_socket.h"

#define CREATE_CODE 0x01
#define JOIN_CODE 0x02
#define MOVE_CODE 0x03
#define STOP_MOVE_CODE 0x04

#define IDF_CODE 0x01
#define P90_CODE 0x02
#define SCOUT_CODE 0x03

#define SURVIVAL_CODE 0x01
#define CLEAR_ZONE_CODE 0x02

#define RIGHT_CODE 0x01
#define LEFT_CODE 0x02
#define UP_CODE 0x03
#define DOWN_CODE 0x04
#define UP_RIGHT_CODE 0x05
#define UP_LEFT_CODE 0x06
#define DOWN_RIGHT_CODE 0x07
#define DOWN_LEFT_CODE 0x08

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
    
        void stop();
};
#endif  // COMMON_PROTOCOL_H_