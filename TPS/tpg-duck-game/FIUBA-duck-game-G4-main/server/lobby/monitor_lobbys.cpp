#include "monitor_lobbys.h"




MonitorLobbys::MonitorLobbys() {}


void MonitorLobbys::shutdown(){
    std::lock_guard<std::mutex> lock(mtx);
    for(auto& lobby  : this->list){
        lobby.stop();
    }
}

size_t MonitorLobbys::size() { 
    std::lock_guard<std::mutex> lock(mtx);
    return list.size(); 
}




MonitorLobbys::~MonitorLobbys() {
    std::lock_guard<std::mutex> lock(mtx);
    for(auto& lobby  : this->list){
        if(lobby.is_alive()){
            lobby.stop();
        }
        lobby.join();
    }
}



