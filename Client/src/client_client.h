#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <stdint.h>
#include <string>
#include "client_protocol.h"
#include "common_commanddto.h"
#include "common_responsedto.h"
#include "common_queue.h"
/*
 * TDA Client
 * Representa una conexión al servidor.
 */
class Client {
    private:
        ClientProtocol protocol;
        //Queue<Command> sdl_events;
        //Queue<Command> snapshot;

    public:
        /*
         * Constructor de Client, recibe los parámetros para la conexión.
         */
        explicit Client(
                const std::string& hostname,
                const std::string& servname);

        /*
         * Método el cual ejecuta la lógica del cliente:
         * - levantar comandos.
         * - enviarlos por medio del protocolo .
         * - recibir mensajes en caso de ser indicado.
         */
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
