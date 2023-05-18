#include "server_client_writer.h"
#include "common_liberror.h"

ClientWriter::ClientWriter(ServerProtocol *protocol, Queue<Snapshot*> *q) :
    protocol(protocol), q(q), talking(true), alive(true) {}

void ClientWriter::run() {
    while (talking) {
        try {
            Snapshot* response = q->pop();
            response->print(false);
            protocol->sendSnapshot(*response);
            delete response;
        } catch (const ClosedQueue&) {
             break;
        } catch (const LibError& err) {
            // socket closed
        }
    }
    alive = false;
}

void ClientWriter::stop() {
    talking = false;
}

bool ClientWriter::ended() {
    return !alive;
}

ClientWriter::~ClientWriter() {
    join();
}
