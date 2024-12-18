#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "common_socket.h"

#define MAX_LENGTH_BUFFER 512

class Protocol {
private:
    Socket skt;
protected:
    bool was_closed = false;
    void send_string(const std::string& string);
    void send_2_bytes(const uint16_t& bytes);
    void send_byte(const uint8_t& byte);
    void receive_string(std::string& string);
    void receive_2_bytes(uint16_t& bytes);
    void receive_byte(uint8_t& byte);
    
public: 
    explicit Protocol(char* hostname, char* servname);
    explicit Protocol(Socket&& skt);
    void kill();
};

#endif
