#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <list>
#include <mutex>
#include <string>

#include "../common_src/common_queue.h"
#include "server_command.h"

class Monitor {
private:
    Queue<Command> receiver_queue;
    std::mutex mtx_receiver;
    // cppcheck-suppress unusedStructMember
    std::list<Queue<Message*>*> list_queues_sender;
    std::mutex mtx_sender;

public:
    Monitor();
    void broadcast(Message* message);
    Queue<Message*>* new_sender();
    void clear_queue(Queue<Message*>* queue);
    void clear_queues();
    void push_command(const Command& command);
    Queue<Command>& get_receiver_queue();
    void clear_receiver();
};

#endif
