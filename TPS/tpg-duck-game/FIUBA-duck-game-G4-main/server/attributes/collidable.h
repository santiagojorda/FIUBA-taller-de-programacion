#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <cstdint>
#include <memory>
#include <iostream>

class GameLogic;
class Player;
class Equippable;
class Positionable;
class Ground;
class Banana;
class Box;
class Projectile;

class Collidable : public std::enable_shared_from_this<Collidable> {
public:
    virtual void handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) = 0;

    virtual void on_collision_with(Player& player, GameLogic& game_logic);
    virtual void on_collision_with(std::shared_ptr<Equippable> equip, GameLogic& game_logic);
    virtual void on_collision_with(std::shared_ptr<Ground> surface, GameLogic& game_logic);
    virtual void on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic);
    virtual void on_collision_with(std::shared_ptr<Box> box, GameLogic& game_logic);
    virtual void on_collision_with(std::shared_ptr<Banana> banana, GameLogic& game_logic);

    virtual ~Collidable() = default;
};

#endif // COLLIDABLE_H