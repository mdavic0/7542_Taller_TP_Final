#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <stdint.h>
#include <string>
#include "common_socket.h"
#include "client_protocol.h"
#include "common_eventdto.h"
#include "common_snapshot.h"
#include "common_queue.h"
#include "EventSender.h"
#include "SnapshotReceiver.h"

/*
 * TDA Client
 * Representa una conexión al servidor.
 */
class Client {
    private:
        ClientProtocol protocol;
        Queue<EventDTO*> sdl_events;
        Queue<Snapshot*> snapshot_queue;

    public:
        /*
         * Constructor de Client, recibe los parámetros para la conexión.
         */
        explicit Client(
                const std::string& hostname,
                const std::string& servname);

        void run();

        /*
         * No queremos permitir que alguien haga copias
         * */
        Client(const Client&) = delete;
        Client& operator=(const Client&) = delete;

        /*
         * Queremos permitir mover a los objetos (move semantics).
         *
         * Como todos nuestros atributos son movibles, la implementación
         * por default de C++ nos alcanza.
         * */
        Client(Client&&) = default;
        Client& operator=(Client&&) = default;
};

#endif  // CLIENT_CLIENT_H_
