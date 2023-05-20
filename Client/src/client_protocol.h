#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <sstream>
#include "common_protocol.h"
#include "common_eventdto.h"
#include "common_snapshot.h"
/*
 * TDA ClientProtocol
 * Se comunica con el servidor a través de su socket.
 */
class ClientProtocol : public Protocol {
    private:

        void sendCreate(const std::string& scenario);
        void sendJoin(const uint32_t& code);
        void sendMove();

        Snapshot getCreate();
        Snapshot getJoin();
        Snapshot getMove();
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
