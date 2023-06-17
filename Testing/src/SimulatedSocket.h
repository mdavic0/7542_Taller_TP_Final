#include <cstring>

class SimulatedSocket {
private:
    static const unsigned int MAX_BUFFER_SIZE = 1024;
    char internalBuffer[MAX_BUFFER_SIZE];
    unsigned int bufferStart;
    unsigned int bufferIndex;
    bool isClosed;

public:
    SimulatedSocket() : bufferStart(0), bufferIndex(0), isClosed(false) {
        memset(internalBuffer, 0, sizeof(internalBuffer));
    }

    int sendall(const void *data, unsigned int sz, bool *was_closed) {
        if (isClosed) {
            if (was_closed != nullptr) {
                *was_closed = true;
            }
            return -1;
        }

        const char *inputData = static_cast<const char *>(data);
        unsigned int remainingSize = sz;

        while (remainingSize > 0 && bufferIndex < MAX_BUFFER_SIZE) {
            internalBuffer[bufferIndex++] = *inputData++;
            remainingSize--;
        }

        if (remainingSize > 0) {
            if (was_closed != nullptr) {
                *was_closed = true;
            }
            isClosed = true;  // Simulate socket closure
            return -1;
        }

        if (was_closed != nullptr) {
            *was_closed = false;
        }
        return sz;
    }

    int recvall(void *data, unsigned int sz, bool *was_closed) {
        if (isClosed) {
            if (was_closed != nullptr) {
                *was_closed = true;
            }
            return -1;
        }

        char *outputData = static_cast<char *>(data);
        unsigned int remainingSize = sz;

        while (remainingSize > 0 && bufferStart < bufferIndex) {
            *outputData++ = internalBuffer[bufferStart++];
            remainingSize--;
        }

        if (remainingSize > 0) {
            if (was_closed != nullptr) {
                *was_closed = true;
            }
            isClosed = true;  // Simulate socket closure
            return -1;
        }

        if (was_closed != nullptr) {
            *was_closed = false;
        }
        return sz;
    }
};
