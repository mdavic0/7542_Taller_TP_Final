#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>
#include <sstream>
#include "common_socket.h"
#include "common_eventdto.h"
#include "common_snapshot.h"

/*
 * TDA ServerProtocol.
 * Se comunica con el cliente a través de su socket.
 */
class ServerProtocol {
    private:
        MockSocket& peer;

        /*
         * Ante un comando create, rearma el EventDTO
         * que representa dicho comando.
         */
        EventDTO getCreate();

        /*
         * Ante un comando join, rearma el EventDTO
         * que representa dicho comando.
         */
        EventDTO getJoin();

        /*
         * Ante un comando broadcast, rearma el EventDTO
         * que representa dicho comando.
         */
        EventDTO getBroadcast();

        /*
         * Envía la respuesta de un
         * comando create
         */
        void responseCreate(uint32_t code);

        /*
         * Envía la respuesta de un
         * comando join
         */
        void responseJoin(uint8_t ok);

        /*
         * Envía la respuesta de un
         * comando broadcast
         */
        void responseBroadcast(const std::string& str);

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
         * Método privado para enviar strings al servidor.
         */
        void sendString(const std::string& str);

        /*
         * Método privado para recibir strings
         */
        std::string recvString();

    public:
        /*
         * Constructor de ServerProtocol recibe el socket con el que
         * debe comunicarse con el cliente.
         */
        explicit ServerProtocol(
                MockSocket& skt);

        EventDTO getEvent();

        void sendSnapshot(
            const Snapshot &snapshot);

        void stop();

        /*
         * No queremos permitir que alguien haga copias
         * */
        ServerProtocol(const ServerProtocol&) = delete;
        ServerProtocol& operator=(const ServerProtocol&) = delete;

        /*
         * Queremos permitir mover a los objetos (move semantics).
         *
         * Como todos nuestros atributos son movibles, la implementación
         * por default de C++ nos alcanza.
         * */
        ServerProtocol(ServerProtocol&&) = default;
        ServerProtocol& operator=(ServerProtocol&&) = default;
};

#endif  // SERVER_PROTOCOL_H_