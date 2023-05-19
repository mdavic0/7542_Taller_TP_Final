#include "server_server.h"
#include <utility>
#include <algorithm>
#include "EventReceiver.h"
#include "server_games_controller.h"
#include "common_liberror.h"

Server::Server(const std::string& servname) :
    skt(servname.c_str()), readers(), controller(), talking(true), alive(true) {}

void Server::endedClients() {
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

void Server::waitClients() {
    for (auto *reader : readers) {
        reader->stop();   // join is inside stop method
        delete reader;
    }
}

void Server::run() {
    while (talking) {
        try {
            Socket peer = skt.accept();
            EventReceiver *reader = new EventReceiver(std::move(peer), controller);
            //  Se lanza hilo lector
            reader->start();
            readers.push_back(reader);   //  Agrego cliente
            endedClients();
        } catch (const LibError& err) {
            // socket closed
            break;
        }
    }
    alive = false;
}

void Server::stop() {
    talking = false;
    skt.shutdown(2);
    skt.close();
}

bool Server::ended() {
    return !alive;
}

Server::~Server() {
    waitClients();
    join();
}

