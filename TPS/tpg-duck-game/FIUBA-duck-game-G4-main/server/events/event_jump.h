#ifndef EVENT_JUMP_H
#define EVENT_JUMP_H

#include "event.h"

class EventJump: public Event {
public:
    explicit EventJump(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override;
    ~EventJump();
};

#endif 
