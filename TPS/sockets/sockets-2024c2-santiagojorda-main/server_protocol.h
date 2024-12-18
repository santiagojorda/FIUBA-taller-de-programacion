#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>

#include "common_duck.h"
#include "common_socket.h"

class ServerProtocol {
private:
    Socket skt;
    Socket peer;

public:
    explicit ServerProtocol(const char* servname);

    void send_message(const std::string& message);

    void receive_message(std::string& message, bool& was_closed);

    void send_byte_message(uint8_t data);
};

#endif
