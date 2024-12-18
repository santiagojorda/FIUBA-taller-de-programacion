#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include "../common_src/common_queue.h"
#include "../common_src/common_thread.h"
#include "server_message.h"
#include "server_monitor.h"
#include "server_protocol.h"

class Sender: public Thread {
private:
    // cppcheck-suppress unusedStructMember
    Queue<Message*>* queue;
    ServerProtocol& protocol;
    bool is_running = true;
    Monitor& monitor;

public:
    explicit Sender(Monitor& monitor, ServerProtocol& protocol);

    void run() override;
    void kill();
};

#endif
