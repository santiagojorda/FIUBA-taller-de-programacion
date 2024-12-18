#ifndef MONITOR_LOBBYS_H
#define MONITOR_LOBBYS_H

#include <utility>    
#include "lobby.h"

class MonitorLobbys{
private:
    std::list<Lobby> list;
    std::mutex mtx;
public:
    MonitorLobbys();

    template <typename... Args>
    void add_item(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx);
        list.emplace_back(std::forward<Args>(args)...);
        list.back().start();
    }

    
    void shutdown();

    size_t size();

    ~MonitorLobbys();
};











#endif // MONITOR_LOBBYS_H
