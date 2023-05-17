#include "client_client.h"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        //  ./client 127.0.0.1 8080

        if (argc != 3) {
            std::cerr << "Bad program call. Expected " << argv[0]
                << " <ip/hostname server> <puerto/servicename>\n";
            return 1;
        }

        Client client(argv[1], argv[2]);
        client.run();
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
