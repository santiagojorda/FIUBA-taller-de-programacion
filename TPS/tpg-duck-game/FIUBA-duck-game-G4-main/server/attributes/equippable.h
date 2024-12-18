
#ifndef EQUIPPABLE_H
#define EQUIPPABLE_H

#include <memory>
#include "positionable.h"
#include "../../common/coordinate.h"
#include "collidable.h"

class Inventory;
class GameLogic;
class Player;
class Projectile;
enum class EquippableState: uint8_t {
    DEAD,
    ALIVE,
};

class Equippable : public Positionable, public Collidable {
private:
    EquippableState state;
    uint8_t frame;

public:
    Equippable();
    Equippable(const uint8_t _texture_id);
    explicit Equippable(const uint8_t& _texture_id, const Coordinate& _coordinate);
    virtual void update(GameLogic& game_logic);
    virtual void handle_equip(Inventory& inventory) = 0;

    using Collidable::on_collision_with;
    virtual void on_collision_with(Player& player, GameLogic& game_logic) override;
    virtual void on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) override;
    virtual void handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) override;

    void die();
    bool is_dead();
    virtual uint8_t send_frame();
};

#endif 