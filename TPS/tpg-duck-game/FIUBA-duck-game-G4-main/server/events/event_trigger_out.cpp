#include "event_trigger_out.h"

EventTriggerOut::EventTriggerOut(uint8_t& _player_id) : Event(_player_id, ActionEvent::TRIGGER_OUT){}

void EventTriggerOut::execute(GameLogic& game_logic){
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        player.shoot(game_logic, ModeShoot::TRIGGER_OUT);
    });
 }; 
EventTriggerOut::~EventTriggerOut() {};