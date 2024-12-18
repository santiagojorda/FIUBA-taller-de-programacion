#ifndef ACCEPTOR_LOBBYS_H
#define ACCEPTOR_LOBBYS_H


#include "../../common/socket.h"
#include "../../common/queue.h"
#include "../protocol/protocol_lobby.h"

#include "monitor_lobbys.h"

class AcceptorLobbys : public Thread{
private:
    MonitorLobbys& monitor;
    Queue<std::string>& queue;

public:
    AcceptorLobbys(MonitorLobbys& _monitor, Queue<std::string>& _queue);

    void run() override;

    ~AcceptorLobbys();
};











#endif // ACCEPTOR_LOBBYS_H
