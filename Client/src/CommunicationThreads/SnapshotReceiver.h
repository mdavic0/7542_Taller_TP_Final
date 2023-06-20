#ifndef LEFT4DEAD_SNAPSHOTRECEIVER_H
#define LEFT4DEAD_SNAPSHOTRECEIVER_H
#include "Thread.h"
#include "Queue.h"
#include "ClientProtocol.h"
#include "Snapshot.h"
#include "Socket.h"
#include <atomic>
#include <memory>

class SnapshotReceiver : public Thread {
private:
    std::shared_ptr<Socket> skt;
    ClientProtocol<Socket> protocol;
    Queue<std::shared_ptr<Snapshot>>& snapshot_queue;
    std::atomic<bool> talking;
    std::atomic<bool> alive;
    bool& endGame;
public:
    SnapshotReceiver(std::shared_ptr<Socket> skt,
                     Queue<std::shared_ptr<Snapshot>>& snapshots, bool& endGame);

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
