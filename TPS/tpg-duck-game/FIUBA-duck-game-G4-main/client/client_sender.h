#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "../common/queue.h"
#include "../common/thread.h"
#include "protocol/protocol_client.h"

#include "client_event.h"

class ClientSender: public Thread {
private:
    ClientProtocol& protocol;
    // El client es el dueño de la queue
    Queue<ClientEvent_t>& commands;

public:
    /*
     * Constructor.
     */
    ClientSender(ClientProtocol& protocol, Queue<ClientEvent_t>& commands);

    virtual void run() override;

    virtual ~ClientSender();
    // el is_running y moving_left luego se van
    /*
     * Event processing:
     * - If window is closed, or Q or Escape buttons are pressed, quit the application.
     * - If Right key is pressed, character would run.
     * - If Right key is released, character would stop.
     */

    // void procesar_comando(SDL_Event& event, bool& is_running, bool& is_moving_left);

    /*
        Deshabilitar copias.
    */
    ClientSender(const ClientSender&) = delete;
    ClientSender& operator=(const ClientSender&) = delete;
};

#endif  // CLIENT_SENDER_H
