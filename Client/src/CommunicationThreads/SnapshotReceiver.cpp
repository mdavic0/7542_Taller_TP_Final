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
            std::cout << "Client sanp Queue closed " << std::endl;
            break;
        } catch (const LibError &exc) {     // sql quit 2, server ends q and slow client 1
            snapshot_queue.close();
            std::cout << "Client sanp recv closed" << std::endl;
            break;
        } catch (const std::exception& exc) {
            std::cout << "SnapshotReceiver - Exception occurred test log: " << exc.what() << std::endl;
        }
    }
    alive = false;
}

void SnapshotReceiver::stop() {
    talking = false;
    std::cout << "SnapshotReceiver - stop " << std::endl;
}

bool SnapshotReceiver::ended() {
    return !alive;
}

SnapshotReceiver::~SnapshotReceiver() {
    std::cout << "SnapshotReceiver - delete " << std::endl;
    join();
}
