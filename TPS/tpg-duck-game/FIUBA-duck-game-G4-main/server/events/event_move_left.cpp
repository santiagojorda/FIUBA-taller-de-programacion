#include "event_move_left.h"

EventMoveLeft::EventMoveLeft(uint8_t& _player_id) : Event(_player_id, ActionEvent::MOVE_LEFT){}

void EventMoveLeft::execute(GameLogic& game_logic){
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        player.run_left(game_logic);
    });
}; 
EventMoveLeft::~EventMoveLeft() {};