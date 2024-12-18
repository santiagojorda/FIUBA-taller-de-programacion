
#include "server.h"

Server::Server(std::string& server_name) : skt(server_name.c_str()),  monitor(), queue(), acceptor_lobby(monitor, queue), is_alive(false), controler(skt){
    this->acceptor_lobby.start();
    this->controler.start();
}


void Server::run(){
    this->is_alive = true;

    try {
        while (this->is_alive) {
            std::string server_name;
            Socket skt_client = this->skt.accept();
            ProtocolLobby protocl_loby(skt_client);
           uint8_t type;
           protocl_loby.recv_connection_type(type);
           switch (type) {
           case (int)ConnectionType::HOST:
               protocl_loby.recv_server_name(server_name);
               this->queue.push(server_name);
               break;
            case (int)ConnectionType::JOIN:
                protocl_loby.send_number_lobbys(this->monitor.size());
            default:
                break;
           }
       }
        this->close();
    } catch (const std::exception& e) {
        this->close();
        std::cerr << e.what() << '\n';
    }
}

void Server::close(){
    if(this->is_alive){
        this->is_alive = false;
    }
}

Server::~Server() {
    this->close();
    this->skt.close();
    this->queue.close();
    this->acceptor_lobby.stop();
    this->acceptor_lobby.join();
    this->controler.join();
}
