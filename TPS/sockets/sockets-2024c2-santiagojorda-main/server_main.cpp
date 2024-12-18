#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "common_socket.h"
#include "server_server.h"

#define SUCCESS 0
#define ERROR -1

int main(int argc, char const* argv[]) {

    try {
        if (argc == 2) {
            const char* port = argv[1];
            Server server(port);
            server.start_shopping();
            return SUCCESS;
        } else {
            std::cerr << "Bad call. " << argv[0] << " <port>" << std::endl;
            return ERROR;
        }
    } catch (std::exception& error) {
        std::cerr << "Server error: " << error.what() << std::endl;
        return ERROR;
    } catch (...) {
        std::cerr << "Server error. There is not information." << std::endl;
        return ERROR;
    }
}
