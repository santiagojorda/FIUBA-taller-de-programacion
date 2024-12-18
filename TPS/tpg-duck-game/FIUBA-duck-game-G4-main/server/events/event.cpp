#include "event.h"

#include <iostream>

Event::Event(uint8_t& _player_id, const ActionEvent& _action_event)
    : player_id(_player_id),
    action_event(_action_event)
    {}


void Event::start(GameLogic& game_logic) {
    game_logic.handle_event(*this);
}

void Event::execute_player_action(GameLogic& game_logic, const uint8_t& player_id, std::function<void(Player&, GameLogic&)> action) {
    try {
        Player& player = game_logic.get_player(player_id);
        action(player, game_logic);
    } catch (const std::exception& e) {
        std::cerr << "No se ejecuto comando, no existe player de id " << int(player_id) << ": " << e.what() << std::endl;
    }
}

Event::~Event() {

}