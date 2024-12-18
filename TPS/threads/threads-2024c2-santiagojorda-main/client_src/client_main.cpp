#include <exception>
#include <iostream>
#include <string>

#include "client_client.h"

#define ARGS_EXPECTED 3  // ./client 127.0.0.1 8080 -> <executable> <hostname> <servname>
#define SUCCESS 0
#define BAD_ARGUMENTS 1
#define ERROR -1


int main(int argc, char* argv[]) {
    try {
        if (argc == ARGS_EXPECTED) {
            char* hostname = argv[1];
            char* servname = argv[2];

            Client client(hostname, servname);
            client.run();
            return SUCCESS;
        } else {
            std::cerr << "Bad call " << argv[0] << " <hostname> <servname>" << std::endl;
            return BAD_ARGUMENTS;
        }
    } catch (std::exception& error) {
        std::cerr << "Client error: " << error.what() << std::endl;
        return ERROR;
    } catch (...) {
        std::cerr << "Client error. There is not information." << std::endl;
        return ERROR;
    }
}
