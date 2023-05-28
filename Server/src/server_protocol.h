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
        EventDTO getStopMove();
        EventDTO getStart();
        void sendCreate(uint32_t code);
        void sendJoin(uint8_t ok);
        void sendPlaying(std::map<TypeOperator, std::pair<uint16_t, uint16_t>> &playersInfo);
        void sendOperator(TypeOperator typeOperator);
        void sendPosition(const uint16_t& x, const uint16_t& y);

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
        void stop();
};

#endif  // SERVER_PROTOCOL_H_