#include "SnapshotSender.h"
#include "Liberror.h"

SnapshotSender::SnapshotSender(std::shared_ptr<Socket> skt,
                               Queue<std::shared_ptr<Snapshot>>& q) :
    skt(skt), snapshot_queue(q), talking(true), alive(true) {}

void SnapshotSender::run() {
    while (talking) {
        try {
            std::shared_ptr<Snapshot> response = snapshot_queue.pop();
            protocol.sendSnapshot(response, skt);
        } catch (const ClosedQueue& exc) {      // client leaver or slow,  server ends with q
            skt->shutdown(2);
            skt->close();
            break;
        } catch (const LibError& exc) {
            break;
        } catch (const std::exception& exc) {
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
