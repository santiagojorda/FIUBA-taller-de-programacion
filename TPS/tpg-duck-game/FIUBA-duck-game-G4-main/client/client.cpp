#include "client.h"

#include <iostream>

enum N_players { ONE_PLAYER = 1, TWO_PLAYER, MAX_PLAYER = 2 };

Client::Client(const std::string& hostname, const std::string& servname):
        skt(hostname.c_str(), servname.c_str()),
        protocol(skt),
        commands(),
        game_state(),
        receiver(protocol, game_state),
        sender(protocol, commands),
        drawer(commands, game_state) {

    this->protocol.send_init(ONE_PLAYER);
}

Client::Client(const std::string& hostname, const std::string& servname, int N_players):
        skt(hostname.c_str(), servname.c_str()),
        protocol(skt),
        commands(),
        game_state(),
        receiver(protocol, game_state),
        sender(protocol, commands),
        drawer(commands, game_state) {

    this->protocol.send_init(N_players > MAX_PLAYER ? MAX_PLAYER : N_players);
}

Client::Client(Socket&& socket, int cant_players):
        skt(std::move(socket)),
        protocol(skt),
        commands(),
        game_state(),
        receiver(protocol, game_state),
        sender(protocol, commands),
        drawer(commands, game_state) {
    this->protocol.send_init(static_cast<uint8_t>(cant_players));
}

void Client::run() {
    receiver.start();
    sender.start();
}

void Client::active_drawer() {
    drawer.run();

    this->skt.shutdown(2);
    this->commands.close();
}


Client::~Client(){

    receiver.stop();
    sender.stop();

    receiver.join();
    sender.join();
}
