#ifndef BULLET_BOUNCE_H
#define BULLET_BOUNCE_H

#include "bullet.h"

class BulletBounce: public Bullet {
private:
public:
    explicit BulletBounce(const ProjectileRange& _range_tiles, const Coordinate& _coordinate,
                          const Direction& _direction, const int& _dispersion_angle,
                          const uint8_t& _shooter_id);

    void bounce(const Positionable& superfice);

    using Collidable::on_collision_with;
    virtual void on_collision_with(std::shared_ptr<Ground> surface, GameLogic& game_logic) override;
    ~BulletBounce();
};


#endif  // BULLET_BOUNCE_H
