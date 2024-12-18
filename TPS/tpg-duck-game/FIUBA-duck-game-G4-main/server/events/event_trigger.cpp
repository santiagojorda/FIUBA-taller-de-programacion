#include "event_trigger.h"

EventTrigger::EventTrigger(uint8_t& _player_id) : Event(_player_id, ActionEvent::TRIGGER){}

void EventTrigger::execute(GameLogic& game_logic){
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        player.shoot(game_logic, ModeShoot::TRIGGER);
    });
}; 
EventTrigger::~EventTrigger() {};