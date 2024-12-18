#include <exception>
#include <iostream>

#include "server_server.h"

#define ERROR -1
#define SUCCESS 0
#define BAD_ARGUMENTS 1

#define ARGS_EXPECTED 2

int main(int argc, char* argv[]) {

    try {
        if (argc == ARGS_EXPECTED) {
            char* servname = argv[1];
            Server server(servname);
            server.run();
            return SUCCESS;
        } else {
            std::cerr << "Bad call " << argv[0] << " <servname>" << std::endl;
            return BAD_ARGUMENTS;
        }

    } catch (const std::exception& error) {
        std::cerr << "Server error: " << error.what() << std::endl;
        return ERROR;
    } catch (...) {
        std::cerr << "Server error. There is not information." << std::endl;
        return ERROR;
    }
}
