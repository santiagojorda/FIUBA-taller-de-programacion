#ifndef SERVER_POSITIONABLE_H_
#define SERVER_POSITIONABLE_H_

#include <cstdint>
#include <memory>
#include "../../common/rectangle.h"
class GameLogic;
class Bullet;
class Player;
class Box;
class Equippable;
class Projectile;

class Positionable {

private:
    uint8_t texture_id;

protected:
    uint8_t id = 0;
    Rectangle space;

public:
    Positionable();
    Positionable(const uint8_t& _id);
    Positionable(const uint8_t& _id, const uint8_t& _texture_id, const Coordinate& _coordinate);
    Positionable(const uint8_t& _texture_id, const Coordinate& _coordinate);

    Coordinate get_coordinate() const;

    void set_coordinate(const Coordinate& new_coordinate);

    Rectangle get_rectangle() const;

    virtual void translate();
    virtual void translate_x(int steps);
    virtual void translate_y(int steps);
    virtual void fall(GameLogic& game_logic);
    uint8_t get_id() const;
    uint8_t get_texture_id() const;


    virtual ~Positionable();
};

#endif  
