#include "Acceptor.h"
#include "Server.h"
#include <utility>
#include <algorithm>
#include "EventReceiver.h"
#include "GamesController.h"
#include "Liberror.h"

Acceptor::Acceptor(const std::string &servname) :
        skt(servname.c_str()), readers(), controller(), talking(true), alive(true) {}

void Acceptor::endedClients() {
    if (readers.empty()) {
        return;
    }

    readers.erase(std::remove_if(readers.begin(), readers.end(),
                                 [](auto* reader){
                                     if (reader->ended()) {
                                         delete reader;
                                         return true;
                                     } else {
                                         return false;
                                     }
                                 }), readers.end());
}

void Acceptor::waitClients() {
    for (auto *reader : readers) {
        reader->stop();   // join is inside stop method
        delete reader;
    }
}

void Acceptor::run() {
    while (talking) {
        try {
            std::shared_ptr<Socket> peer = std::make_shared<Socket>(skt.accept());
            EventReceiver *reader = new EventReceiver(peer, controller);
            reader->start();
            readers.push_back(reader);   //  Agrego cliente
            endedClients();
        } catch (const LibError& err) {
            // socket closed
            break;
        } catch (const std::exception& exc) {
            break;
        }
    }

    alive = false;
}

void Acceptor::stop() {
    talking = false;
    skt.shutdown(2);
    skt.close();
}

bool Acceptor::ended() {
    return !alive;
}

Acceptor::~Acceptor() {
    waitClients();
    join();
}
