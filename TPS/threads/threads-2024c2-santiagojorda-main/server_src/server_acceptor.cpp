#include "server_acceptor.h"

#include <iostream>
#include <list>
#include <string>
#include <utility>

#include "server_client.h"

Acceptor::Acceptor(const std::string& servname, Monitor& monitor):
        skt_acceptor(servname.c_str()), client_list(), monitor(monitor) {}

void Acceptor::listen_new_client() {
    Socket skt_new_client = skt_acceptor.accept();
    ServerClient* new_client = new ServerClient(std::move(skt_new_client), monitor);
    client_list.push_back(new_client);
}

void Acceptor::run() {

    try {
        while (is_running) {
            listen_new_client();
            remove_desconnected_clients();
        }
        stop();
    } catch (...) {
        stop();
    }
    remove_all_clients();
}

void Acceptor::remove_desconnected_clients() {
    client_list.remove_if([](ServerClient* client) {
        if (!client->is_alive()) {
            client->close();
            delete client;
            return true;
        }
        return false;
    });
}

void Acceptor::remove_all_clients() {
    for (ServerClient* client: client_list) {
        client->close();
        delete client;
    }
    client_list.clear();
}

void Acceptor::stop() {
    if (is_running) {
        is_running = false;
        skt_acceptor.shutdown(2);
        skt_acceptor.close();
    }
}
