#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <string>

#include "common_socket.h"

class ClientProtocol {
private:
    Socket skt;

public:
    explicit ClientProtocol(char* hostname, char* servname);

    void send_message(std::string& message);

    int receive_byte_message();
    void receive_message(std::string& message, bool& was_closed);
};


#endif
