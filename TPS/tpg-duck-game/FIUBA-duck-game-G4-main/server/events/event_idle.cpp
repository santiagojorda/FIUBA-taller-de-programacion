#include "event_idle.h"

EventIdle::EventIdle(uint8_t& _player_id) : Event(_player_id, ActionEvent::IDLE){}

void EventIdle::execute(GameLogic& game_logic) {
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        (void)game_logic;
        player.idle();
    });
} 
EventIdle::~EventIdle() {};