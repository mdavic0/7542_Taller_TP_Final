// "Copyright [2023] <mdavic0>"  [©legal/copyright]

#include <iostream>
#include "src/server_Server.h"

int main(int argc, char *argv[]) { try {
    int ret = 1;
    if (argc != 2) {
        std::cerr << "Bad program call. Expected "
                  << argv[0] << " <puerto/servicename>" << std::endl;
        return ret;
    }
    const char *servicename = argv[1];

    Server srv(servicename);
    srv.run();

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
    }
}

