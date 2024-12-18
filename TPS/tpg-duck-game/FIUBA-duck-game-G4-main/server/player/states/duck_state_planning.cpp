#include "duck_state_planning.h"

struct PlanningStateConfig {
    DuckStateType id = DuckStateType::PLANNING;
    std::string name = "Planning";
};
PlanningStateConfig planning_config;

DuckStatePlanning::DuckStatePlanning(const uint8_t& _player_id):
        DuckState(planning_config.id, planning_config.name,
                  duck_state_frames[planning_config.id].max_frames, _player_id) {}

void DuckStatePlanning::update_state(Player& player, GameLogic& game_logic) {
    (void)game_logic;
    (void)player;
    if (has_reached_max_frames()) {
        reset();
    }
}

void DuckStatePlanning::execute(Player& player, GameLogic& game_logic) {
    (void)player;
    (void)game_logic;
    increment_frame();
}

DuckStatePlanning::~DuckStatePlanning() {}