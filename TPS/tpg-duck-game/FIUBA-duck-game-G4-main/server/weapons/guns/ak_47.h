#ifndef AK_47_H
#define AK_47_H

#include "../gun.h"

class AK47: public Gun {
private:
public:
    explicit AK47(const Coordinate& _coordinate);

    // Dispara aumentado dispersion
    void trigger(ListProjectiles& projectiles, const uint8_t& player_id) override;

    // reinicia dispersion
    virtual void trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                             bool& was_dropped) override;

    ~AK47();
};

#endif
