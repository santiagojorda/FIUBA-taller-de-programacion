#ifndef BULLET
#define BULLET

#include "../../attributes/updatable.h"
#include "../projectile.h"

#define MAX_RANGE_TILES 1  // medio

class GameLogic;

class Bullet: public Projectile {
private:
    uint8_t steps = 0;

protected:
    double dispersion_angle;  // radianes

public:
    explicit Bullet(const ProjectileRange& _range_tiles, const Coordinate& _coordinate,
                    const Direction& _direction, const int& _dispersion_angle,
                    const uint8_t& _shooter_id);


    void update(GameLogic& game_logic) override;
};

#endif
