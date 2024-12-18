#include "keyboard_controller.h"

#include <SDL2/SDL.h>

KeyboardController::KeyboardController(Queue<ClientEvent_t>& _commands, int _num_players):
        commands(_commands), num_players(_num_players) {}

enum PlayerKeyboard { PLAYER_1, PLAYER_2 };

void KeyboardController::procesar_comando(SDL_Event& event) {
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            throw std::runtime_error("Cierre del juego");
        }

        // Este evento ocurre cuando una tecla es presionada
        if (event.type == SDL_KEYDOWN) {
            procesar_keydown(event);
            // Este evento ocurre cuando la tecla es liberada
        } else if (event.type == SDL_KEYUP) {
            procesar_keyup_player_1(event);
            if (num_players == 2) {
                procesar_keyup_player_2(event);
            }
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    procesar_accion_player_1(state);

    if (num_players == 2) {
        procesar_accion_player_2(state);
    }
}

void KeyboardController::procesar_keyup_player_1(SDL_Event& event) {
    ClientEvent_t client_event;
    switch (event.key.keysym.sym) {
        case SDLK_d:
            client_event = {PLAYER_1, ActionEvent::IDLE};
            this->commands.push(client_event);
            break;
        case SDLK_a:
            client_event = {PLAYER_1, ActionEvent::IDLE};
            this->commands.push(client_event);
            break;
        case SDLK_e:
            client_event = {PLAYER_1, ActionEvent::TRIGGER_OUT};
            this->commands.push(client_event);
            break;
        case SDLK_s:
            client_event = {PLAYER_1, ActionEvent::IDLE};
            this->commands.push(client_event);
            break;
    }
}

void KeyboardController::procesar_keyup_player_2(SDL_Event& event) {
    ClientEvent_t client_event;
    switch (event.key.keysym.sym) {
        case SDLK_j:
            client_event = {PLAYER_2, ActionEvent::IDLE};
            this->commands.push(client_event);
            break;
        case SDLK_l:
            client_event = {PLAYER_2, ActionEvent::IDLE};
            this->commands.push(client_event);
            break;
        case SDLK_o:
            client_event = {PLAYER_2, ActionEvent::TRIGGER_OUT};
            this->commands.push(client_event);
            break;
    }
}

void KeyboardController::procesar_keydown(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
            throw std::runtime_error("Cierre del juego");
        default:
            break;
    }
}

void KeyboardController::procesar_accion_player_1(const Uint8* state) {
    ClientEvent_t client_event;

    if (state[SDL_SCANCODE_D]) {
        client_event = {PLAYER_1, ActionEvent::MOVE_RIGHT};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_A]) {
        client_event = {PLAYER_1, ActionEvent::MOVE_LEFT};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_W]) {
        client_event = {PLAYER_1, ActionEvent::JUMP};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_E]) {
        client_event = {PLAYER_1, ActionEvent::TRIGGER};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_R]) {
        client_event = {PLAYER_1, ActionEvent::DROP_GUN};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_F]) {
        std::cout << "Apuntando hacia arriba" << std::endl;
    }
    if (state[SDL_SCANCODE_S]) {
        client_event = {PLAYER_1, ActionEvent::CROUCH};
        this->commands.push(client_event);
    }
}

void KeyboardController::procesar_accion_player_2(const Uint8* state) {
    ClientEvent_t client_event;

    if (state[SDL_SCANCODE_L]) {
        client_event = {PLAYER_2, ActionEvent::MOVE_RIGHT};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_J]) {
        client_event = {PLAYER_2, ActionEvent::MOVE_LEFT};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_I]) {
        client_event = {PLAYER_2, ActionEvent::JUMP};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_K]) {
        client_event = {PLAYER_2, ActionEvent::CROUCH};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_O]) {
        client_event = {PLAYER_2, ActionEvent::TRIGGER};
        this->commands.push(client_event);
    }
    if (state[SDL_SCANCODE_P]) {
        client_event = {PLAYER_2, ActionEvent::DROP_GUN};
        this->commands.push(client_event);
    }
}
