#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>

#include <arpa/inet.h>

#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"

class ServerProtocol: public Protocol {

public:
    explicit ServerProtocol(Socket& socket);
    void send_message_box_appeared();
    void send_message_picked_up_box(const std::string& player_name, const uint8_t& reward_id);
    void receive_message_picked_up_box(std::string& player_name, uint8_t& box_id);
};

#endif
