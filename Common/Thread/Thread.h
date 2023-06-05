#ifndef SERVER_THREAD_H_
#define SERVER_THREAD_H_

#include <thread>
#include <iostream>

class Thread {
    private:
        std::thread thread;

    public:
        Thread();

        void start();

        void join();

        void main();

        virtual void run() = 0;
        virtual void stop() = 0;
        virtual ~Thread();

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&& other) = delete;
        Thread& operator=(Thread&& other) = delete;
};

#endif  // SERVER_THREAD_H_
