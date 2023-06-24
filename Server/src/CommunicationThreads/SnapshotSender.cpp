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
            // delete response;
        } catch (const ClosedQueue& exc) {      // client slow or quit sdl
            std::cout << "SnapshotSender - snap Queue closed " << std::endl;
            skt->shutdown(2);
            skt->close();
            break;
        } catch (const LibError& exc) {     // server ends whit q input
            snapshot_queue.close();
            std::cout << "SnapshotSender - socket closed " << std::endl;
            break;
        } catch (const std::exception& exc) {
            std::cout << "SnapshotSender - Exception occurred test log: " << exc.what() << std::endl;
            break;
        }
    }
    alive = false;
}

void SnapshotSender::stop() {
    std::cout << "SnapshotSender - stop " << std::endl;
    talking = false;
}

bool SnapshotSender::ended() {
    return !alive;
}

SnapshotSender::~SnapshotSender() {
    std::cout << "SnapshotSender - delete " << std::endl;
    join();
}
