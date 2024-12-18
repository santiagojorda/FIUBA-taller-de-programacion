#ifndef ACTION_COMMANDS_H
#define ACTION_COMMANDS_H

#include <cstdint>

enum HeaderProtocol {
    HEADER_CLIENT = 0xA,
    HEADER_SERVER = 0xB,
};

enum class ActionEvent : uint8_t {
    MOVE_LEFT,        // Moverse a la izquierda
    MOVE_RIGHT,       // Moverse a la derecha
    JUMP,             // Salta / aletear
    GRAB_OR_RELEASE,  // Tomar / soltar un arma/casco/armadura
    AIM_UP,           // Apuntar hacia arriba
    CROUCH,           // Tirarse al piso
    IDLE,             // Nada
    TRIGGER,          // Apretar el gatillo
    TRIGGER_OUT,      // Soltar el gatillo
    DROP_GUN          // SOltar Arma
};

#endif  // ACTION_COMMANDS_H
