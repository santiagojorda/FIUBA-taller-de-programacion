#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


#include "server_protocol.h"
#include <arpa/inet.h>
#include <string>

class Message {
public:
    Message();
    virtual void send(ServerProtocol& protocol) = 0;
    virtual void print() = 0;
    virtual Message* clone() = 0;
    virtual ~Message() = default;
};

class PickedUpMessage: public Message {
private:
    // cppcheck-suppress unusedStructMember
    std::string player_name;
    // cppcheck-suppress unusedStructMember
    uint8_t reward_id;

public:
    explicit PickedUpMessage(const std::string& player_name, const uint8_t reward_id);
    void send(ServerProtocol& protocol) override;
    void print() override;
    Message* clone() override { return new PickedUpMessage(*this); }
};

class BoxAppearedMessage: public Message {
public:
    void send(ServerProtocol& protocol) override;
    void print() override;
    Message* clone() override { return new BoxAppearedMessage(*this); }
};

#endif
