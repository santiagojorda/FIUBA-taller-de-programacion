#include "event_drop_gun.h"

EventDropGun::EventDropGun(uint8_t& _player_id) : Event(_player_id, ActionEvent::DROP_GUN){}

void EventDropGun::execute(GameLogic& game_logic){
    execute_player_action(game_logic, player_id, [](Player& player, GameLogic& game_logic) {
        player.drop_gun(game_logic);
    });
}; 
EventDropGun::~EventDropGun() {};