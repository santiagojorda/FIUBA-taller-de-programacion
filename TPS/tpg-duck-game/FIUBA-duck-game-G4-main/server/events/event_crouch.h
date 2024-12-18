#ifndef EVENT_CROUCH_H
#define EVENT_CROUCH_H

#include "event.h"

class EventCrouch: public Event {
public:
    explicit EventCrouch(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override; 
    ~EventCrouch();
};

#endif 