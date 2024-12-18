#ifndef EVENT_MOVE_LEFT_H
#define EVENT_MOVE_LEFT_H

#include "event.h"

class EventMoveLeft: public Event {
public:
    explicit EventMoveLeft(uint8_t& _player_id);

    virtual void execute(GameLogic& game_logic) override; 
    ~EventMoveLeft();
};

#endif
