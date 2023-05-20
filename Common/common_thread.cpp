#include "common_thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(&Thread::main, this);
}

void Thread::join() {
    thread.join();
}

void Thread::main() {
    try {
        this->run();
    } catch(const std::exception &err) {
        std::cerr << "Unexpected exception: " << err.what() << "\n";
    } catch(...) {
        std::cerr << "Unexpected exception: <unknown>\n";
    }
}

Thread::~Thread() {
}
