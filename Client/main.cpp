// "Copyright [2023] <mdavic0>"  [©legal/copyright]

#include <iostream>
#include "client_Client.h"

int main(int argc, char *argv[]) { try {
    int ret = 1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected "
                  << argv[0] << " <ip/hostname server> "
                                "<puerto/servicename> " << std::endl;
        return ret;
    }

    const char *hostname = argv[1];
    const char *port = argv[2];

    Client client(hostname, port);
    client.run();

    ret = 0;
    return ret;
} catch (const std::exception& err) {
    std::cerr
            << "Something went wrong and an exception was caught: "
            << err.what()
            << "\n";
    return -1;
} catch (...) {
    std::cerr << "Something went wrong and an unknown exception was caught.\n";
    return -1;
} }
