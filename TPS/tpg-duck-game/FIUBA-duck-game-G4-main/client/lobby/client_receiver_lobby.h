#ifndef CLIENT_RECEIVER_LOBBY_H
#define CLIENT_RECEIVER_LOBBY_H

#include "../../common/queue.h"
#include "../../common/thread.h"
#include "../protocol/protocol_client.h"

#include "game_data.h"

class ClientReceiverLobby: public Thread {
private:
    ClientProtocol& protocol;
    Queue<game_data_t>& game_data;

public:
    ClientReceiverLobby(ClientProtocol& protocol, Queue<game_data_t>& game_data);

    virtual void run() override;

    virtual ~ClientReceiverLobby();
};

#endif  // CLIENT_RECEIVER_LOBBY_H
