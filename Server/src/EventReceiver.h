#ifndef SERVER_CLIENT_READER_H_
#define SERVER_CLIENT_READER_H_

#include "common_thread.h"
#include "server_protocol.h"
#include "GamesController.h"
#include "SnapshotSender.h"
#include <atomic>
#include <map>

/*
 * TDA Client. Representa una conexión aceptada por el servidor.
 * Hilo lector.
 */
class EventReceiver : public Thread {
    private:
        ServerProtocol protocol;
        Queue<EventDTO*>* event_queue;
        Queue<Snapshot*> snapshot_queue;
        SnapshotSender sender;
        GamesController& controller;
        uint32_t game_code;
        std::atomic<bool> talking;
        std::atomic<bool> alive;

    public:
        /*
         * Constructor que recibe el protocolo y la queue de eventos
         * por referencia.
         */
        explicit EventReceiver(Socket&& skt, GamesController& controller);

        /*
         * Método que devuelve true cuando el hilo termino de ejecutarse.
         */
        bool ended();

        /*
         * Método de ejecución del hilo, recibe eventos por medio del
         *  protocolo y realiza la acción correspondiente.
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
        virtual ~EventReceiver();
};

#endif  // SERVER_CLIENT_READER_H_
