#include "SnapshotSender.h"
#include "Liberror.h"

SnapshotSender::SnapshotSender(ServerProtocol& protocol,
                               Queue<std::shared_ptr<Snapshot>>& q) :
    protocol(protocol), snapshot_queue(q), talking(true), alive(true) {}

void SnapshotSender::run() {
    while (talking) {
        try {
            std::shared_ptr<Snapshot> response = snapshot_queue.pop();
            protocol.sendSnapshot(response);
            // delete response;
        } catch (const ClosedQueue&) {
            break;
        } catch (const LibError& err) {
            break;
        }
    }
    alive = false;
}

void SnapshotSender::stop() {
    talking = false;
}

bool SnapshotSender::ended() {
    return !alive;
}

SnapshotSender::~SnapshotSender() {
    join();
}
