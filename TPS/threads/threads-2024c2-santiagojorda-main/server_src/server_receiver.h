#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include "../common_src/common_queue.h"
#include "../common_src/common_thread.h"
#include "server_command.h"
#include "server_monitor.h"
#include "server_protocol.h"

class Receiver: public Thread {
private:
    Monitor& monitor;
    ServerProtocol& protocol;
    bool is_running = true;

public:
    explicit Receiver(Monitor& monitor, ServerProtocol& protocol);
    void run() override;
    void kill();
    bool running_status();
};

#endif
