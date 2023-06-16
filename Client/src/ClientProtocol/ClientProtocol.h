#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <sstream>
#include "Protocol.h"
#include "EventDTO.h"
#include "Snapshot.h"
/*
 * TDA ClientProtocol
 * Se comunica con el servidor a través de su socket.
 */
class ClientProtocol : public Protocol {
    private:

        void sendCreate(const std::string& scenario, const TypeOperator& typeOperator, const TypeGame& typeGame);
        void sendJoin(const uint32_t& code, const TypeOperator& typeOperator);
        void sendStart();
        void sendMove(const MoveTo& moveTo, const uint8_t& idPlayer);
        void sendStopMove(const MoveTo& moveTo, const uint8_t& idPlayer);
        void sendSmoke(const uint8_t& idPlayer);
        void sendStopSmoke(const uint8_t& idPlayer);
        void sendGrenade(const uint8_t& idPlayer);
        void sendStopGrenade(const uint8_t& idPlayer);
        void sendBlitz(const uint8_t& idPlayer);
        void sendShoot(const uint8_t& idPlayer);
        void sendStopShoot(const uint8_t& idPlayer);
        void sendLeave(const uint8_t& idPlayer);
        void sendOperator(const TypeOperator& typeOperator);
        void sendMoveTo(const MoveTo& moveTo);
        void sendId(const uint8_t& idPlayer);

        Snapshot getCreate();
        Snapshot getJoin();
        Snapshot getStart();
        Snapshot getPlaying();
        Snapshot getEnd();
        Snapshot getStats();
        std::vector<StOperator> getPlayers();
        std::vector<EnemyDto> getEnemies();
        std::vector<ObstacleDto> getObstacles();
    public:
        /*
        * Constructor que llama al constructor del padre
        * */
        explicit ClientProtocol(
            Socket&& skt);

        /*
         * Método generico para indicar al servidor que sucedio un evento.
         */
        void sendEvent(const EventDTO& eventdto);
        
        /*
         * Método generico recibir un snapshot del servidor.
         */
        Snapshot getSnapshot();

        /*
        * No queremos permitir que alguien haga copias
        * */
        ClientProtocol(const ClientProtocol&) = delete;
        ClientProtocol& operator=(const ClientProtocol&) = delete;

        /*
        * Queremos permitir mover a los objetos (move semantics).
        *
        * Como todos nuestros atributos son movibles, la implementación
        * por default de C++ nos alcanza.
        * */
        ClientProtocol(ClientProtocol&&) = default;
        ClientProtocol& operator=(ClientProtocol&&) = default;
};
#endif  // CLIENT_PROTOCOL_H_
