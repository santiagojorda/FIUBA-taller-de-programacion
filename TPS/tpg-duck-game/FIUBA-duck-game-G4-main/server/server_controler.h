#ifndef SERVER_CONTROLER_H
#define SERVER_CONTROLER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include <iostream>

#define CLOSE 'q'

class ServerControler : public Thread{
private:
    Socket& skt_server;
public:
    ServerControler(Socket& _skt_server);

    void run() override;

    ~ServerControler();
};

#endif // SERVER_CONTROLER_H
