#ifndef SERVER_H
#define SERVER_H

#include "lobby/acceptor_lobbys.h"
#include "../common/queue.h"
#include "protocol/protocol_server.h"
#include "server_controler.h"

class Server{
private:
    Socket skt;
    MonitorLobbys monitor;
    Queue<std::string> queue;
    AcceptorLobbys acceptor_lobby;
    std::atomic<bool> is_alive;
    ServerControler controler;

public:
    Server(std::string& server_name);

    void run();

    void close();

    ~Server();
};


#endif // SERVER_H
