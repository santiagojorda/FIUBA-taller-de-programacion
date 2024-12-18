#include "server_monitor.h"

#include <iostream>

#define MAX_SIZE_QUEUE 20

Monitor::Monitor(): receiver_queue(MAX_SIZE_QUEUE), list_queues_sender() {}

Queue<Message*>* Monitor::new_sender() {
    std::unique_lock<std::mutex> lock(mtx_sender);
    Queue<Message*>* new_queue = new Queue<Message*>(MAX_SIZE_QUEUE);
    Message* msj;
    while (new_queue->try_pop(msj)) {
        msj->print();
    }
    list_queues_sender.push_back(new_queue);
    return new_queue;
}

void Monitor::broadcast(Message* message) {
    std::unique_lock<std::mutex> lock(mtx_sender);

    for (Queue<Message*>* sender_queue: list_queues_sender) {
        Message* message_cloned = message->clone();
        sender_queue->try_push(message_cloned);
    }
}

void Monitor::clear_queue(Queue<Message*>* queue) {

    std::unique_lock<std::mutex> lock(mtx_sender);
    Message* message;
    while (queue->try_pop(message)) {
        delete message;
    }

    queue->close();

    list_queues_sender.remove(queue);
    delete queue;
}

Queue<Command>& Monitor::get_receiver_queue() {
    std::unique_lock<std::mutex> lock(mtx_receiver);
    return receiver_queue;
}

void Monitor::push_command(const Command& command) {
    std::unique_lock<std::mutex> lock(mtx_receiver);
    receiver_queue.push(command);
}

void Monitor::clear_receiver() {

    std::unique_lock<std::mutex> lock(mtx_receiver);
    receiver_queue.close();
}

void Monitor::clear_queues() {
    for (Queue<Message*>* queue: list_queues_sender) {
        Message* message;
        while (queue->try_pop(message)) {
            delete message;
        }
        queue->close();
        delete queue;
    }
    list_queues_sender.clear();
    clear_receiver();
}
