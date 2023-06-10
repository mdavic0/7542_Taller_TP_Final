#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <string>
#include <sstream>
#include "Protocol.h"
#include "EventDTO.h"
#include "Snapshot.h"

/*
 * TDA ServerProtocol.
 * Se comunica con el cliente a través de su socket.
 */
class ServerProtocol : Protocol {
    private:
    
        EventDTO getCreate();
        EventDTO getJoin();
        EventDTO getStart();
        EventDTO getMove();
        EventDTO getStopMove();
        EventDTO getSmoke();
        EventDTO getStopSmoke();
        EventDTO getGrenade();
        EventDTO getStopGrenade();
        EventDTO getBlitz();
        EventDTO getShoot();
        EventDTO getStopShoot();
        EventDTO getLeave();
        void sendCreate(const uint32_t& code, const uint8_t& idPlayer);
        void sendJoin(const uint8_t& ok, const uint8_t& idPlayer, const uint8_t& size);
        void sendStart(const std::vector<StOperator> &playersInfo, const TypeGame& typeGame, const uint8_t& idMap);
        void sendPlaying(const std::vector<StOperator> &playersInfo);
        void sendOperator(const TypeOperator& typeOperator);
        void sendState(const State& state);
        void sendPlayersInfo(const std::vector<StOperator> &playersInfo);
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