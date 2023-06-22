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
        } catch (const LibError &exc) {
            snapshot_queue.close();
            break;
        } catch (const std::exception& exc) {
            std::cout << "Exception occurred custom: " << exc.what() << std::endl;
        }
    }
    alive = false;
}

void SnapshotReceiver::stop() {
    talking = false;
    //snapshot_queue.close(); // ????
}

bool SnapshotReceiver::ended() {
    return !alive;
}

SnapshotReceiver::~SnapshotReceiver() {
    join();
}
