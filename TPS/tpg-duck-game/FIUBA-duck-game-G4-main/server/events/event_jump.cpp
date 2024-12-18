#include "event_jump.h"

EventJump::EventJump(uint8_t& _player_id) : Event(_player_id, ActionEvent::JUMP){}

void EventJump::execute(GameLogic& game_logic){
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        (void)game_logic;
        player.jump();
    });
}; 

EventJump::~EventJump() {};