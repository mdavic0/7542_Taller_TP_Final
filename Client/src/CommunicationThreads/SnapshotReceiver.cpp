#include "SnapshotReceiver.h"
#include "Liberror.h"

SnapshotReceiver::SnapshotReceiver(std::shared_ptr<Socket> skt,
                                   Queue<std::shared_ptr<Snapshot>> &snapshots, bool& endGame) :
        skt(skt), snapshot_queue(snapshots), talking(true), alive(true), endGame(endGame) {
}

void SnapshotReceiver::run() {
    while (talking) {
        try {
            snapshot_queue.push(std::make_shared<Snapshot>(protocol.getSnapshot(skt)));
        } catch (const ClosedQueue& exc){
            break;
        } catch (const LibError &exc) {     // sql quit 2, server ends q and slow client 1
            snapshot_queue.close();
            break;
        } catch (const std::exception& exc) {
        }
    }
    alive = false;
}

void SnapshotReceiver::stop() {
    talking = false;
}

bool SnapshotReceiver::ended() {
    return !alive;
}

SnapshotReceiver::~SnapshotReceiver() {
    join();
}
