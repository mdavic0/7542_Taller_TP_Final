#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>
#include <sstream>
#include "common_protocol.h"
#include "common_eventdto.h"
#include "common_snapshot.h"

/*
 * TDA ServerProtocol.
 * Se comunica con el cliente a través de su socket.
 */
class ServerProtocol : Protocol {
    private:
    
        EventDTO getCreate();
        EventDTO getJoin();
        EventDTO getMove();
        void sendCreate(uint32_t code);
        void sendJoin(uint8_t ok);
        void sendMove();

    public:
        /*
        * Constructor que llama al constructor del padre
        * */
        explicit ServerProtocol(
                Socket&& skt);

        EventDTO getEvent();

        void sendSnapshot(
            const Snapshot &snapshot);

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