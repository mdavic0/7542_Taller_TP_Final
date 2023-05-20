#ifndef LEFT4DEAD_ACCEPTOR_H
#define LEFT4DEAD_ACCEPTOR_H
#include <string>
#include <vector>
#include <atomic>
#include "common_thread.h"
#include "EventReceiver.h"
#include "common_socket.h"


class Acceptor : public Thread {
    private:
        Socket skt;
        std::vector<EventReceiver*> readers;
        GamesController controller;
        std::atomic<bool> talking;
        std::atomic<bool> alive;

        void endedClients();
        void waitClients();

    public:
        /*
        * Constructor de aceptador, recibe el servidor donde va a escuchar.
        */
        explicit Acceptor(const std::string& servname);

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
        * la ejecución, ademas realiza el join.
        */
        virtual ~Acceptor();
};


#endif //LEFT4DEAD_ACCEPTOR_H
