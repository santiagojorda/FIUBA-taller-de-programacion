#ifndef EVENT_TRIGGER_H
#define EVENT_TRIGGER_H

#include "event.h"

class EventTrigger: public Event {
public:
    explicit EventTrigger(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override; 
    ~EventTrigger();
};


#endif
