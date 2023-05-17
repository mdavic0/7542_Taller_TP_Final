// "Copyright [2023] <mdavic0>"  [©legal/copyright]

#include <iostream>

int main(int argc, char *argv[]) { try {
    int ret = 1;
    if (argc != 3) {
        std::cerr << "Bad program call. Expected "
                  << argv[0] << " <ip/hostname server> "
                                "<puerto/servicename> " << std::endl;
        return ret;
    }

    //Client client(argv[1], argv[2]);
    //client.run();

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
