#include "SnapshotReceiver.h"
#include "common_liberror.h"

SnapshotReceiver::SnapshotReceiver(ClientProtocol &protocol,
    Queue<Snapshot*> &snapshots, bool& endGame) :
    protocol(protocol), snapshot_queue(snapshots), talking(true), alive(true), endGame(endGame) {
}

void SnapshotReceiver::run() {
    while (talking && !endGame) {
        try {
            Snapshot* snapshot = new Snapshot(protocol.getSnapshot());
            snapshot_queue.push(snapshot);
        } catch (const ClosedQueue& err){
            talking = false;
        } 
        // catch (const LibError& err) {
        //     talking = false;
        //     // socket closed
        //     // break;
        // }
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
