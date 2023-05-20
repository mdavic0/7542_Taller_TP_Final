#ifndef LEFT4DEAD_SNAPSHOTRECEIVER_H
#define LEFT4DEAD_SNAPSHOTRECEIVER_H
#include "common_thread.h"
#include "common_queue.h"
#include "client_protocol.h"
#include "common_snapshot.h"
#include <atomic>

class SnapshotReceiver : public Thread {
    private:
        ClientProtocol& protocol;
        Queue<Snapshot*>& snapshot_queue;
        std::atomic<bool> talking;
        std::atomic<bool> alive;
    public:
        SnapshotReceiver(ClientProtocol& protocol, Queue<Snapshot*>& snapshots);

        /*
        * Método que devuelve true cuando el hilo termino de ejecutarse.
        */
        bool ended();

        /*
        * Método de ejecución del hilo, recibe snapshots por medio del
        * protocolo y los pushea a la queue de snapshots.
        */
        virtual void run() override;

        /*
        * Método para detener la iteración en la cual se reciben
        * snapshots por medio del protocolo.
        */
        virtual void stop() override;

        virtual ~SnapshotReceiver();
};


#endif //LEFT4DEAD_SNAPSHOTRECEIVER_H
