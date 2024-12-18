#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "../gun.h"


class LaserRifle: public Gun {
public:
    LaserRifle(const Coordinate& _coordinate);

    // Dispara aumentado dispersion
    void trigger(ListProjectiles& projectiles, const uint8_t& player_id) override;

    ~LaserRifle();
};
#endif
