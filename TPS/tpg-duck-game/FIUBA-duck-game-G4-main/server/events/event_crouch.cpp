#include "event_crouch.h"

EventCrouch::EventCrouch(uint8_t& _player_id) : Event(_player_id, ActionEvent::CROUCH){}

void EventCrouch::execute(GameLogic& game_logic){
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        (void)game_logic;
        player.crouch();
    });
}; 
EventCrouch::~EventCrouch() {};