#include "SnapshotSender.h"
#include "common_liberror.h"

SnapshotSender::SnapshotSender(ServerProtocol& protocol, Queue<Snapshot*>& q) :
    protocol(protocol), snapshot_queue(q), talking(true), alive(true) {}

void SnapshotSender::run() {
    while (talking) {
        try {
            Snapshot* response = snapshot_queue.pop();
            std::cout << "enviando snapshot" << std::endl;
            protocol.sendSnapshot(*response);
            // delete response;
        } catch (const ClosedQueue&) {
             break;
        } catch (const LibError& err) {
            // socket closed
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
