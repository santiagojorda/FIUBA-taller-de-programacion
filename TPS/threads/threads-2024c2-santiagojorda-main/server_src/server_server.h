#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <string>

class Server {
private:
    // cppcheck-suppress unusedStructMember
    std::string servname;

public:
    explicit Server(const std::string& servname);

    void run();
};

#endif
