#include "Server.h"

Server::Server(const char * servicename) : acceptor(servicename) {}

void Server::run() { try {
        // Se lanza el hilo aceptador
        this->acceptor.start();

        // El servidor leerá por entrada estándar y cerrará el programa
        // de forma ordenada cuando lea la letra q
        while (std::cin.get() != 'q') {}

        this->acceptor.stop();
    } catch (const std::exception& err) {
        std::cerr
                << "Something went wrong and an exception was caught: "
                << err.what()
                << "\n";
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
    }
}
