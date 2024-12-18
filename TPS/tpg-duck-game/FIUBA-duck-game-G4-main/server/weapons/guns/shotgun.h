#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "../gun.h"


class Shotgun: public Gun {
private:
    bool reloaded;
    bool blocked;

public:
    Shotgun(const Coordinate& _coordinate);

    // dispara o libera el cartucho
    virtual void trigger(ListProjectiles& projectiles, const uint8_t& player_id) override;

    virtual void trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                             bool& was_dropped) override;

    ~Shotgun();
};

#endif
