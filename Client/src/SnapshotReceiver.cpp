#include "SnapshotReceiver.h"
#include "Liberror.h"

SnapshotReceiver::SnapshotReceiver(ClientProtocol &protocol,
    Queue<Snapshot*> &snapshots, bool& endGame) :
    protocol(protocol), snapshot_queue(snapshots), talking(true), alive(true), endGame(endGame) {
}

void SnapshotReceiver::run() {
    while (talking) {
        try {
            Snapshot* snapshot = new Snapshot(protocol.getSnapshot());
            snapshot_queue.push(snapshot);
        } catch (const ClosedQueue& err){
            talking = false;
            break;
        } 
    }
    alive = false;
}

void SnapshotReceiver::stop() {
    talking = false;
    // protocol.stop(); ????
}

bool SnapshotReceiver::ended() {
    return !alive;
}

SnapshotReceiver::~SnapshotReceiver() {

}
