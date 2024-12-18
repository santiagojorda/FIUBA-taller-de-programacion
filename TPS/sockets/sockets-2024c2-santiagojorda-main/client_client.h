#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <string>

#include "client_protocol.h"
#include "common_duck.h"

class Client {
private:
    ClientProtocol protocol;
    Duck duck;

    void get_status();
    void print_message(const std::string& message);

public:
    explicit Client(char* hostname, char* servname);

    void shopping();
};

#endif
