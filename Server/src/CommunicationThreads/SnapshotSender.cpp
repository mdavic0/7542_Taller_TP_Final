#include "SnapshotSender.h"
#include "Liberror.h"

SnapshotSender::SnapshotSender(Socket *skt,
                               Queue<std::shared_ptr<Snapshot>>& q) :
    skt(skt), snapshot_queue(q), talking(true), alive(true) {}

void SnapshotSender::run() {
    while (talking) {
        try {
            std::shared_ptr<Snapshot> response = snapshot_queue.pop();
            protocol.sendSnapshot(*response, skt);
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
