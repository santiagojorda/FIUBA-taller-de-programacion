#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <string>

#include "client_protocol.h"

class Client {
private:
    ClientProtocol protocol;

public:
    explicit Client(char* hostname, char* servname);

    void run();
};

#endif
