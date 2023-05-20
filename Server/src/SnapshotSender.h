#ifndef SERVER_CLIENT_WRITER_H_
#define SERVER_CLIENT_WRITER_H_

#include "common_thread.h"
#include "common_queue.h"
#include "server_protocol.h"
#include <atomic>
#include <map>

/*
 * TDA Client. Representa una conexión aceptada por el servidor.
 * Hilo escritor.
 */
class SnapshotSender : public Thread {
    private:
        ServerProtocol& protocol;
        Queue<Snapshot*>& snapshot_queue;
        std::atomic<bool> talking;
        std::atomic<bool> alive;

    public:
        /*
         * Constructor recibe protocolo por referencia, el cual contiene
         * el socket por el cual se envían respuestas.
         * Además, recibe una queue por referencia, de la cual obtendrá
         * las respuestas que debe enviar.
         */
        explicit SnapshotSender(ServerProtocol& protocol, Queue<Snapshot*>& snapshot_queue);

        /*
         * Método que devuelve true cuando el hilo termino de ejecutarse.
         */
        bool ended();

        /*
         * Método que encapsula la ajecucion del hilo. Recibe respuestas a
         * enviar por medio de la queue, y las envia por medio del protocolo.
         */
        virtual void run() override;

        /*
         * Método para detener la iteración en la cual se envían
         * respuestas por medio del protocolo. El cierre del socket
         * lo hace el hilo lector.
         */
        virtual void stop() override;

        /*
         * Destructor que realiza el join del hilo.
         */
        virtual ~SnapshotSender();
};

#endif  // SERVER_CLIENT_WRITER_H_
