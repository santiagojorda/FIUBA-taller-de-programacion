#include "round_manager.h"

#include <algorithm>

RoundManager::RoundManager(const ListPlayers& players) {
    for (const auto& player: players) {
        this->statistics.count_winer[player.get_texture_id()] = 0;
    }
}

bool RoundManager::check_winer(const ListPlayers& players){
    int lives = players.size();
    uint8_t id_winer = 0xFF;
    for (const auto& player: players) {
        if(player.is_dead_animation_finished()){
            lives--;
        }  else {
            id_winer = player.get_texture_id();
        }
    }
    if(lives <= 1){
        this->statistics.rounds++;
        this->statistics.count_winer[id_winer] ++;
        auto it = std::max_element( this->statistics.count_winer.begin(),  this->statistics.count_winer.end(),
        [](const auto& pair1, const auto& pair2) {
            return pair1.second < pair2.second;
        });
        this->statistics.id_winer = it->first;
        return true;
    }
    return false;
}



void RoundManager::log_state(std::ostream& log,  const GameState_t& state){

    log << std::endl  << "+====================================+:" << std::endl;
    log << "Players Win: "<< (int)state.statistics.id_winer << " ronuds wind: " <<  state.statistics.count_winer.at(state.statistics.id_winer)<<  std::endl;
    log << "Players:" << std::endl;
    for (const auto& player : state.players) {
    log << "  - Player ID: " << (int)  player.get_texture_id()  << " Cordinate:"<< player.get_coordinate() << std::endl;
    log << " - Round wining: " <<  state.statistics.count_winer.at(player.get_texture_id())<< std::endl;

    }

    log << "Map Items:" << std::endl;
    for (const auto& item : state.map_items) {
        log << "  - Item ID: " << (int)item.texture_id << " Cordinate:"<< item.coordinate  << std::endl;
    }

    log << "Map Projectiles:" << std::endl;
    for (const auto& projectile : state.map_projectiles) {
        log << "  - Projectile ID: " << (int) projectile.texture_id << " Cordinate:"<< projectile.coordinate << std::endl;
    }
    
    log << std::endl  << "+====================================+:" << std::endl;
}

int RoundManager::get_rounds() const { return this->statistics.rounds; }

int RoundManager::get_rounds_winer() { return this->statistics.count_winer[this->statistics.id_winer]; }

uint8_t RoundManager::id_winer() const { return this->statistics.id_winer; }


game_statistics_t RoundManager::get_statistics() const { return this->statistics; }


RoundManager::~RoundManager() {}


