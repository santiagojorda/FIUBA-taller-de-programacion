#ifndef BANANA_H
#define BANANA_H

#include "../gun.h"

class Banana: public Gun {
private:
public:
    explicit Banana(const Coordinate& _coordinate);

    void trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                     bool& was_dropped) override;
    // void on_collision_with(Collidable& other, GameLogic& game_logic) override;
    using Equippable::on_collision_with;
    void on_collision_with(Player& player, GameLogic& game_logic) override;

    void handle_equip(Inventory& inventory) override;
    ~Banana();
};

#endif
