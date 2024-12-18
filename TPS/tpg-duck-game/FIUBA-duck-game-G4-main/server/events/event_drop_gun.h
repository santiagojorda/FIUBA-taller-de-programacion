#ifndef EVENT_DROP_GUN_H
#define EVENT_DROP_GUN_H

#include "event.h"

class EventDropGun: public Event {
public:
    explicit EventDropGun(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override; 
    ~EventDropGun();
};

#endif 