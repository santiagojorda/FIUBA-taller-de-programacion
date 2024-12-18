#ifndef CLIENT_EVENT_H
#define CLIENT_EVENT_H

#include <cstdint>

#include "../common/action_events.h"

struct ClientEvent_t  // es para el keyword -> tiene los command clients y el id de player para
                      // pushearlo en la queue de commands (envio al servidor)
{
    uint8_t id_player;
    ActionEvent action;
};

#endif  // CLIENT_EVENT_H
