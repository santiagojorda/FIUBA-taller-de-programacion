#ifndef PROTOCOL_LOBBY_H
#define PROTOCOL_LOBBY_H

#include <cstdint>

enum class ConnectionType : uint8_t { HOST, JOIN };

#include "../../common/protocol.h"
#include "../../common/socket.h"


class ProtocolLobby : public Protocol{
private:
public:
    ProtocolLobby(Socket& skt);

    void recv_server_name(std::string& server_name);

    void recv_connection_type(uint8_t& type);

    void send_number_lobbys(const uint8_t& send);

    ~ProtocolLobby();
};


#endif  // PROTOCOL_LOBBY_H
