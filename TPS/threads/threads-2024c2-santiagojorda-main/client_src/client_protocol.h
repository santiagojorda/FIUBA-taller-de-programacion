#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "../common_src/common_protocol.h"

class ClientProtocol: public Protocol {
public:
    explicit ClientProtocol(char* hostname, char* servname);
    void send_message_pickup(const std::string& message, const uint8_t& box_id);
    void receive_n_messages(const uint8_t& num_messages, std::vector<std::string>& messages);
};

#endif
