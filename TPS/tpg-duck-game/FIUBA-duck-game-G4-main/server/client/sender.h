#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../game/game_state.h"
#include "../protocol/protocol_server.h"

class Sender: public Thread {
private:
    Queue<GameState_t>& queue;
    ProtocolServer& protocol;

public:
    explicit Sender(Queue<GameState_t>& _queue, ProtocolServer& _protocol);
    void run() override;
    void send(const GameState_t& game_state);

    ~Sender();
};

#endif  // SERVER_SENDER_H_