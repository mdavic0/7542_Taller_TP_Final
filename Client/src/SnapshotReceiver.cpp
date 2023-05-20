#include "SnapshotReceiver.h"
#include "common_liberror.h"

SnapshotReceiver::SnapshotReceiver(ClientProtocol &protocol, Queue<Snapshot*> &snapshots) :
    protocol(protocol), snapshot_queue(snapshots), talking(true), alive(true) {}

void SnapshotReceiver::run() {
    while (talking) {
        try {
            Snapshot* snapshot = new Snapshot(protocol.getSnapshot());
            snapshot_queue.push(snapshot);
        } catch (const LibError& err) {
            // socket closed
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
