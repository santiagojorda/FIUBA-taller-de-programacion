#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <list>
#include <string>

#include "../common_src/common_queue.h"
#include "../common_src/common_socket.h"
#include "server_command.h"
#include "server_monitor.h"
#include "server_protocol.h"
#include "server_receiver.h"
#include "server_sender.h"

class ServerClient {
private:
    Socket skt;
    ServerProtocol protocol;
    Receiver receiver;
    Sender sender;
    Monitor& monitor;

public:
    explicit ServerClient(Socket&& socket, Monitor& monitor);
    void close();
    bool is_alive();
};

#endif
