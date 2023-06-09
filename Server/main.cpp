#include "Server.h"
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include "Defines.h"
#include "Configuration.h"

int main(int argc, char *argv[]) {
    try {
        //  ./server 8080

        if (argc != 2) {
            std::cerr << "Bad program call. Expected "
                << argv[0] << " <servname>\n";
            return 1;
        }

        CF::loadConfiguration(PATH);

        Server server(argv[1]);
        server.run();

        return 0;
    } catch (const std::exception& err) {
        std::cerr
            << "Something went wrong and an exception was caught: "
            << err.what()
            << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return 1;
    }
}
