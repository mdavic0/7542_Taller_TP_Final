#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_
#include "Acceptor.h"
#include <utility>

class Server {
private:
    Acceptor acceptor;
public:
    explicit Server(const char * servicename);
    void run();
};

#endif  // SERVER_SERVER_H_
