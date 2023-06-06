#include "SnapshotReceiver.h"
#include "Liberror.h"

SnapshotReceiver::SnapshotReceiver(ClientProtocol &protocol,
                                   Queue<std::shared_ptr<Snapshot>> &snapshots, bool& endGame) :
        protocol(protocol), snapshot_queue(snapshots), talking(true), alive(true), endGame(endGame) {
}

void SnapshotReceiver::run() {
    while (talking) {
        try {
            snapshot_queue.push(std::make_shared<Snapshot>(protocol.getSnapshot()));
        } catch (const LibError &exc) {
            std::cerr << "receiver: " << exc.what() << std::endl;
            talking = false;
            snapshot_queue.close();
        } catch (const ClosedQueue& err){
            std::cerr << "receiver snap: " << err.what() << std::endl;
            talking = false;
        } catch (...) {}
    }
    std::cout << "termine receiver\n";
    alive = false;
}

void SnapshotReceiver::stop() {
    talking = false;
    snapshot_queue.close(); // ????
}

bool SnapshotReceiver::ended() {
    return !alive;
}

SnapshotReceiver::~SnapshotReceiver() {
    join();
}
