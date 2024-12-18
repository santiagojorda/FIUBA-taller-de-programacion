#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../../common/action_events.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../client_event.h"
#include "../protocol/protocol_client.h"

class KeyboardController {
private:
    Queue<ClientEvent_t>& commands;
    int num_players;

    void procesar_keyup_player_1(SDL_Event& event);

    void procesar_keyup_player_2(SDL_Event& event);

    void procesar_keydown(SDL_Event& event);

    void procesar_accion_player_1(const Uint8* state);

    void procesar_accion_player_2(const Uint8* state);

public:
    /*
     * Constructor.
     */
    KeyboardController(Queue<ClientEvent_t>& _commands, int num_players);

    void procesar_comando(SDL_Event& event);
};

#endif  // KEYBOARD_CONTROLLER_H
