
#include "protocol_lobby.h"


ProtocolLobby::ProtocolLobby(Socket& skt) : Protocol(skt) {}

void ProtocolLobby::recv_server_name(std::string& server_name) { this->receive_string(server_name); }


void ProtocolLobby::recv_connection_type(uint8_t& type) { this->receive_byte(type); }

void ProtocolLobby::send_number_lobbys(const uint8_t& send)  { this->send_byte(send); }


ProtocolLobby::~ProtocolLobby() {}

