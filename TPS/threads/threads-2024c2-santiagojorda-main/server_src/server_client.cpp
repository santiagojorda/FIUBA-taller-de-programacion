#include "server_client.h"

#include <list>
#include <utility>

ServerClient::ServerClient(Socket&& socket, Monitor& monitor):
        skt(std::move(socket)),
        protocol(skt),
        receiver(monitor, protocol),
        sender(monitor, protocol),
        monitor(monitor) {
    receiver.start();
    sender.start();
}

bool ServerClient::is_alive() { return sender.is_alive() && receiver.is_alive(); }

void ServerClient::close() {
    receiver.kill();
    sender.kill();
    receiver.join();
    sender.join();
}
