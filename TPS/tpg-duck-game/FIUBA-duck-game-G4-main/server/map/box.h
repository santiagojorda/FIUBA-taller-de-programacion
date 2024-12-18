#ifndef BOX_H
#define BOX_H

#include <cstdint>
#include "../../common/boxes_id.h"
#include "../attributes/positionable.h"
#include "../attributes/collidable.h"
#include "../attributes/updatable.h"
#include "../attributes/frameable.h"
class Projectile;
class GameLogic;

enum GroundState : uint8_t{
    CLOSE = 0,
    OPEN = 1
};
class Box: public Positionable, public Collidable {
private:
    int tick;
    GroundState state;

public:
    explicit Box(const Coordinate& _coordinate);
    void update();
    void handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) override;
    void drop_weapon(GameLogic& game_logic);
    using Collidable::on_collision_with;
    void on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) override;

    bool is_open();
    void open(GameLogic& game_logic);
    void reset();
    uint8_t get_state();
};
#endif
