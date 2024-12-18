#ifndef EVENT_TRIGGER_OUT_H
#define EVENT_TRIGGER_OUT_H

#include "event.h"

class EventTriggerOut: public Event {
public:
    explicit EventTriggerOut(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override; 
    ~EventTriggerOut();
};


#endif  // EVENT_SHOOT_H
