#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "sprite.h"

struct inventory_t {
    uint8_t weapon;  // si es 0, dejo de leer y salto a armor
    uint8_t ammo;
    uint8_t armor;  // si es 0, dejo de leer y salto a helmet
    uint8_t helmet;
};

struct player_t {
    sprite_t sprite;     //
    uint8_t is_looking;  // hacia donde esta mirando
    uint8_t state;       // si esta parado o bla , con este elijo la animacion
    uint8_t frame;       // que parte de la animacion
    inventory_t inventory;
};

/**
 * DOCUMENTACION
 * sprite_t sprite; vinculado a
    uint8_t is_looking;  hacia donde esta mirando
    uint8_t state;  si esta parado o bla , con este elijo la animacion
    uint8_t frame; que parte de la animacion
    inventory_t inventory; inventario, lo que ocupa el pato
 */

#endif  // PLAYER_H
