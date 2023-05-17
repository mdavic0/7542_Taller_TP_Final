#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "common_socket.h"

int MockSocket::recvall(
        void *data,
        unsigned int sz,
        bool *was_closed) {
    if(sz > 30){
        *was_closed = false;
        return 0;
    }
    *was_closed = false;
    char* aux = (char*)data;
    for(unsigned int i = 0; i < sz; i++){
        aux[i] = array[i];
    }

    return sz;
}


int MockSocket::sendall(
        const void *data,
        unsigned int sz,
        bool *was_closed) {
    if(sz > 30){
        *was_closed = false;
        return 0;
    }
    *was_closed = false;

    char* aux = (char*)data;
    for(unsigned int i = 0; i < sz; i++){
        array[i] = aux[i];
    }

    return sz;
}
