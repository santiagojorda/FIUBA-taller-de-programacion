#ifndef  DIRECTIONABLE_H
#define DIRECTIONABLE_H

#include "../../common/direction.h"


class Directionable{
protected:
    Direction direction;

public:
    Directionable(const Direction& _diretion);

    virtual Direction get_direction();

    virtual void set_direction(const Direction& new_diretion);

    virtual int  get_direction_int();

    bool is_right();
    bool is_left();
    bool is_up();
    bool is_down();

    virtual ~Directionable();
};

#endif // DIRECTIONABLE_H
