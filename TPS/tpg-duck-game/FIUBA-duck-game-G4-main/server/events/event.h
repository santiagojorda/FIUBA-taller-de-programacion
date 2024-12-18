#ifndef EVENT_H
#define EVENT_H

#include <cstdint>

#include <functional>

#include "../../common/action_events.h"
#include "../game/game_logic.h"
#include "../player/player.h"

class Event {
protected:
    // cppcheck-suppress unusedStructMember
    uint8_t& player_id;
    ActionEvent action_event;

    void execute_player_action(GameLogic& game_logic, const uint8_t& player_id, std::function<void(Player&, GameLogic&)> action);

public:
    explicit Event(uint8_t& player_id, const ActionEvent& _action_event);

    virtual void start(GameLogic& game_logic);
    
    virtual void execute(GameLogic& game_logic) = 0; 

    virtual ~Event();
};

#endif  
