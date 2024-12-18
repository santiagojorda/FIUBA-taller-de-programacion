#include "server_server.h"

#include <iostream>
#include <string>
#include <thread>

#include "../common_src/common_queue.h"
#include "server_acceptor.h"
#include "server_game.h"

#define COMMAND_EXIT "q"

Server::Server(const std::string& servname): servname(servname) {}

void Server::run() {

    Monitor monitor;

    Acceptor acceptor(servname.c_str(), monitor);
    acceptor.start();

    Game game(monitor);
    game.start();

    std::string command;
    do {
        std::getline(std::cin, command);
    } while (command != COMMAND_EXIT);

    acceptor.stop();
    game.stop();

    game.join();
    acceptor.join();

    // monitor.clear_queues();
}
