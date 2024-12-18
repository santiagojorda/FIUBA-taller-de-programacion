#include "server_controler.h"



ServerControler::ServerControler(Socket& _skt_server) : Thread(), skt_server(_skt_server) { }

void ServerControler::run(){
    try    {
        std::string commad;
        while (this->_keep_running) {
            std::cout << "q for exit" << std::endl;
            std::cin >> commad;
            switch (commad[0]) {
                case CLOSE:
                    this->skt_server.shutdown(2);
                    this->skt_server.close();
                    this->stop();
                    break;
                default:
                    std::cout << "commad invalid" << std::endl;
                    break;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

ServerControler::~ServerControler() { }
