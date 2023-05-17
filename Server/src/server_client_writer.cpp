#include "server_client_writer.h"
#include "common_liberror.h"

ClientWriter::ClientWriter(ServerProtocol *protocol, Queue<ResponseDTO*> *q) :
    protocol(protocol), q(q), talking(true), alive(true) {}

void ClientWriter::run() {
    while (talking) {
        try {
            ResponseDTO* response = q->pop();
            response->print(false);
            protocol->sendResponse(*response);
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
