#include "client_client.h"
#include "common_liberror.h"

Client::Client(const std::string& hostname, const std::string& servname) :
    protocol(Socket(hostname.c_str(), servname.c_str())),
    sdl_events(100), snapshot_queue(100) {}

void Client::run() {
    EventSender eventSender(this->sdl_events, this->protocol);
    SnapshotReceiver snapshotReceiver(this->protocol, this->snapshot_queue);
    //eventSender.start();
    //snapshotReceiver.start();
    // game.run() ?
}
