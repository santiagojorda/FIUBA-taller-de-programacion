#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>

#include "../../common/coordinate.h"

struct sprite_t {
    uint8_t id_texture;  // ES EL PATH ! tipo de textura -> enum del tipo de arma, piso, pato, etc.
                         // lo tomo y lo mapeo con el sprite -> crear un mapa -> despues se pasa a
                         // .yaml -> elegir color del path
    Coordinate coordinate;
};

struct floor_sprite_t {
    uint8_t path;  // ES EL PATH ! tipo de textura -> enum del tipo de arma, piso, pato, etc.
                   // lo tomo y lo mapeo con el sprite -> crear un mapa -> despues se pasa a
                   // .yaml -> elegir color del path
    uint8_t id_sprite;
    Coordinate coordinate;
};


#endif  // SPRITE_H
