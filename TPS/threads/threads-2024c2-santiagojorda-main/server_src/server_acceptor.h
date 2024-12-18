#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H

#include <list>
#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/common_thread.h"
#include "server_client.h"

class Acceptor: public Thread {
private:
    Socket skt_acceptor;

    // cppcheck-suppress unusedStructMember
    std::list<ServerClient*> client_list;
    void listen_new_client();
    bool is_running = true;
    Monitor& monitor;
    void remove_desconnected_clients();
    void remove_all_clients();

public:
    explicit Acceptor(const std::string& servname, Monitor& monitor);

    void run() override;

    void stop() override;
};

#endif
