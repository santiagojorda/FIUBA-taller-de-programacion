#ifndef CLIENT_HOST_H
#define CLIENT_HOST_H


#include "client.h"

class ClientHost : public Thread {
private:
    Client host;
    const std::string& hostname;
    const std::string& servname;

public:
    ClientHost(const std::string& hostname, const std::string& servname);

    void run() override;

    void init_game();

    ~ClientHost();
};



#endif // CLIENT_HOST_H
