#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>

#include "socket.h"

#define MAX_LENGTH_BUFFER 512

class Protocol {
protected:
    Socket& skt;

protected:
    // cppcheck-suppress unusedStructMember
    bool was_closed;

    void send_string(const std::string& string);
    void send_2_bytes(const uint16_t& bytes);
    void send_byte(const uint8_t& byte);
    void receive_string(std::string& string);
    void receive_2_bytes(uint16_t& bytes);
    void receive_byte(uint8_t& byte);
    void check_is_closed();

public:
    explicit Protocol(Socket& skt);
    void kill();
};

#endif  // COMMON_PROTOCOL_H_