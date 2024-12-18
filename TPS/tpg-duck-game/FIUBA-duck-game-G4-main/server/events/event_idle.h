#ifndef EVENT_IDLE_H
#define EVENT_IDLE_H

#include "event.h"

class EventIdle: public Event {
public:
    explicit EventIdle(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override; 
    ~EventIdle();
};

#endif  