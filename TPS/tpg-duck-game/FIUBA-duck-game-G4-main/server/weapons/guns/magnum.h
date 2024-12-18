#ifndef MAGNUM_H
#define MAGNUM_H

#include "../gun.h"


class Magnum: public Gun {
private:
    bool blocked;

public:
    Magnum(const Coordinate& _coordinate);

    // Dispara aumentado dispersion
    virtual void trigger(ListProjectiles& projectiles, const uint8_t& player_id) override;

    // reinicia dispersion
    virtual void trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                             bool& was_dropped) override;


    ~Magnum();
};

#endif
