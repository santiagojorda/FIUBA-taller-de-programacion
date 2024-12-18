#ifndef GROUND_H
#define GROUND_H

#include <cstdint>
#include <memory>
#include <iostream>

#include "../attributes/positionable.h"
#include "../attributes/collidable.h"

class Projectile;
class GameLogic;

class Ground : public Positionable, public Collidable {
private:
    uint8_t state;

public:
    explicit Ground(const Coordinate& _coordinate, const uint8_t& _texture_id);


    void handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) override;

    using Collidable::on_collision_with;
    void on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) override;

    virtual ~Ground() = default; 
};

#endif // GROUND_H