#ifndef SERVER_CLIENT_READER_H_
#define SERVER_CLIENT_READER_H_

#include "common_thread.h"
#include "server_protocol.h"
#include "server_games_controller.h"
#include "server_client_writer.h"
#include <atomic>
#include <map>

/*
 * TDA Client. Representa una conexión aceptada por el servidor.
 * Hilo lector.
 */
class ClientReader : public Thread {
    private:
        ServerProtocol protocol;
        Queue<ResponseDTO*> q;
        ClientWriter writer;
        GamesController& controller;
        uint32_t game;
        std::atomic<bool> talking;
        std::atomic<bool> alive;

    public:
        /*
         * Constructor recibe un socket ya aceptado y utilizara para
         * comunicarse con ese cliente a través del protocolo.
         * Además, recibe por referencia un GamesController.
         */
        explicit ClientReader(
                Socket&& skt, GamesController& controller);

        /*
         * Método que devuelve true cuando el hilo termino de ejecutarse.
         */
        bool ended();

        /*
         * Método de ejecución del hilo, recibe comandos por medio de
         * su protocolo y realiza la acción correspondiente.
         */
        virtual void run() override;

        /*
         * Método para detener la ejecución el hilo escuchador.
         * Cierra el socket en el cual está escuchando.
         */
        virtual void stop() override;

        /*
         * Destructor que cierra la queue utilizada, termina la
         * ejecución del hilo escritor, ademan realiza el join.
         */
        virtual ~ClientReader();
};

#endif  // SERVER_CLIENT_READER_H_
