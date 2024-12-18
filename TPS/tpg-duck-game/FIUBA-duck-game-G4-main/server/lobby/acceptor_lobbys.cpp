#include "acceptor_lobbys.h"




AcceptorLobbys::AcceptorLobbys(MonitorLobbys& _monitor, Queue<std::string>& _queue) : Thread(),  monitor(_monitor),  queue(_queue) {}

void AcceptorLobbys::run(){
    try
    {
        while (this->is_alive()) {
            std::string server_name  = this->queue.pop();
            monitor.add_item(server_name.c_str());

        }
    }
    catch(const std::exception& e)
    {
        this->stop();
        std::cerr << e.what() << " error acceptor lobby" << '\n';
    }
}


AcceptorLobbys::~AcceptorLobbys() { 
    Thread::~Thread();
}
