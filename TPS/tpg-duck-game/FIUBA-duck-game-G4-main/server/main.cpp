#include <exception>
#include <iostream>
#include <list>



#include "server.h"
#include "yamel/map_deserialize.h"

#define ERROR -1
#define SUCCESS 0
#define BAD_ARGUMENTS 1
#define ARGS_EXPECTED 2

int main(int argc, const char* argv[]) {

    try {
        std::cout << "Iniciando server" << std::endl;

        if (argc == ARGS_EXPECTED) {
            std::string server_name = argv[1];
            Server Server(server_name);
            Server.run();
            Server.close();
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