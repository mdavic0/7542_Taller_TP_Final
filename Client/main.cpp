// "Copyright [2023] <mdavic0>"  [©legal/copyright]

#include <iostream>
#include "client_launcher.h"
#include <QApplication>

int main(int argc, char *argv[]) { 
    try {
        if (argc != 1) {
            std::cerr << "Bad program call. Expected "
                    << argv[0] << std::endl;
            return EXIT_FAILURE;
        }
        QApplication app(argc, argv);
        Launcher launcher;
        launcher.show();
        return app.exec();
    } catch (const std::exception& err) {
        std::cerr
            << "Something went wrong and an exception was caught: "
            << err.what()
            << "\n";
        return -EXIT_FAILURE;
    } catch (...) {
        std::cerr 
            << "Something went wrong and an unknown exception was caught.\n";
        return -EXIT_FAILURE;
    } 
}
