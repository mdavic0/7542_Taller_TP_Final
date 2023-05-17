#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <string>
#include <vector>
#include <atomic>
#include "server_thread.h"
#include "server_client_reader.h"
#include "common_socket.h"

/*
 * TDA Server. Se conectará a un servidor a escuchar conexiones.
 */
class Server : public Thread {
    private:
        Socket skt;
        std::vector<ClientReader*> readers;
        GamesController controller;
        std::atomic<bool> talking;
        std::atomic<bool> alive;

        void endedClients();
        void waitClients();

    public:
        /*
         * Constructor de Server, recibe el servidor donde va a escuchar.
         */
        explicit Server(
                const std::string& servname);

        /*
         * Método que devuelve true cuando el hilo termino de ejecutarse.
         */
        bool ended();

        /*
         * Método para que el Server comience a
         * aceptar conexiones y manejarlas.
         */
        virtual void run() override;

        /*
         * Método para detener la ejecución el hilo aceptador.
         * Cierra el socket en el cual está escuchando.
         */
        virtual void stop() override;

        /*
         * Destructor que termina los hilos lanzados durante
         * la ejecución, ademan realiza el join.
         */
        virtual ~Server();
};

#endif  // SERVER_SERVER_H_
