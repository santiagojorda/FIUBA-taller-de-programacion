#include <cstdint>
#include <iostream>
#include <vector>

#include "client_client.h"
#include "common_socket.h"

#define ERROR -1
#define SUCCESS 0

int main(int argc, char* argv[]) {

    try {
        if (argc == 3) {
            char* hostname = argv[1];
            char* servname = argv[2];
            Client client(hostname, servname);
            client.shopping();
            return SUCCESS;
        } else {
            std::cout << "Bad call " << argv[0] << " <hostname> <servname" << std::endl;
            return ERROR;
        }
    } catch (std::exception& error) {
        std::cerr << "Client error: " << error.what() << std::endl;
        return ERROR;
    } catch (...) {
        std::cerr << "Client error. There is not information." << std::endl;
        return ERROR;
    }
}
