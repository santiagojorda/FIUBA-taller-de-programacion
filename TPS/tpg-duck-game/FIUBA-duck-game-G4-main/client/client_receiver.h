#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "../common/queue.h"
#include "../common/thread.h"
#include "protocol/protocol_client.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& protocol;
    Queue<client_game_state_t>& game_state;

public:
    /*
     * Constructor.
     */
    ClientReceiver(ClientProtocol& protocol, Queue<client_game_state_t>& game_state);

    virtual void run() override;

    virtual ~ClientReceiver();

    // void receiver_data(std::vector<Coordinate>& coordenadas);
};

#endif  // CLIENT_RECEIVER_H
