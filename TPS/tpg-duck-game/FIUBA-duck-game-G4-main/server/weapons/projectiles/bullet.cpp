#include "bullet.h"

#include <cmath>
#include <iostream>

#include "../../game/game_logic.h"
#include "../../map/box.h"

#define TILE_SIZE_BULLET 16

#define TEXTURE_ID 0  // cambiar
#define HORIZONTAL_STEP 4
#define VERTICAL_STEP 2

#define TICKS_PER_STEP 1
#define PI_DEGREES 180
#define WIDTH_BULLET 2
#define HEIGHT_BULLET 2

Bullet::Bullet(const ProjectileRange& _range_tiles, const Coordinate& _coordinate,
               const Direction& _direction, const int& _dispersion_angle,
               const uint8_t& _shooter_id):
        Projectile(TEXTURE_ID, _range_tiles, Coordinate(_coordinate), _direction, _shooter_id),
        dispersion_angle(_dispersion_angle * M_PI / PI_DEGREES)  // lo pasa a radianes
{
    Rectangle cañonaso = this->space;
    int x;
    if (get_direction() == Direction::RIGHT) {
        x = cañonaso.get_x_max();
    } else {
        x = cañonaso.get_x_min();
    }

    // refactorizar
    Coordinate bullet_postion(x, ((cañonaso.get_y_min() + cañonaso.get_y_max()) / 2) - 5, 2, 2);
    this->set_coordinate(bullet_postion);
}


void Bullet::update(GameLogic& game_logic) {
    update_handler.update();

    if ((steps * HORIZONTAL_STEP) / (TILE_SIZE_BULLET) >= (int)range_tiles) {
        die();
        return;
    }

    if (update_handler.is_ready_for_action(TICKS_PER_STEP)) {
        steps++;

        double new_x = HORIZONTAL_STEP * std::cos(dispersion_angle);  // Velocidad inicial en X
        double new_y = VERTICAL_STEP * std::sin(dispersion_angle);    // Velocidad inicial en Y
        // deberia chequear que se pueda (colision)
        new_x *= this->get_direction_int();

        int x = static_cast<int>(std::round(new_x));
        int y = static_cast<int>(std::round(new_y));

        // std::cout << "new bullet position: " << space.get_coordinates() << std::endl;
        game_logic.move(std::dynamic_pointer_cast<Projectile>(shared_from_this()), x, y);
    }
}
