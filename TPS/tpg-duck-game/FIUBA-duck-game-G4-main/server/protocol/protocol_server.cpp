#include "protocol_server.h"

#include "../equipment/armor.h"
#include "../equipment/helmet.h"
#include <memory>

#define BYTE_CLIENT 0xA

ProtocolServer::ProtocolServer(Socket& skt): Protocol(skt) {}

void ProtocolServer::send_coordinates(const Coordinate& send) {
    send_2_bytes(send.get_x());
    send_2_bytes(send.get_y());
    send_2_bytes(send.get_h());
    send_2_bytes(send.get_w());
}

void ProtocolServer::send_inventory(Inventory& inventory) {
    send_gun(inventory.get_gun());
    send_armor(inventory.get_armor());
    send_helmet(inventory.get_helmet());
}

void ProtocolServer::send_gun(std::shared_ptr<Gun> gun) {
    if (gun) {
        send_byte(gun->get_texture_id());
        send_byte(gun->get_ammo());
    } else {
        send_byte(false);
    }
}

void ProtocolServer::send_armor(std::shared_ptr<Armor> armor) {
    if (armor) {
        send_byte(armor->get_texture_id());
    } else {
        send_byte(false);
    }
}
void ProtocolServer::send_helmet(std::shared_ptr<Helmet> helmet) {
    if (helmet) {
        send_byte(helmet->get_texture_id());
    } else {
        send_byte(false);
    }
}

void ProtocolServer::send_players_state(GameState_t& state) {
    uint8_t count_players = state.players.size();
    send_byte(count_players);
    for (Player& player: state.players) {
        send_byte(player.get_texture_id());
        send_coordinates(player.get_coordinate());
        send_byte(static_cast<uint8_t>(player.get_direction()));
        send_byte(static_cast<uint8_t>(player.get_state()));
        send_byte(static_cast<uint8_t>(player.get_frame()));
        send_inventory(player.get_inventory());
    }
}

void ProtocolServer::send_projectiles_state(GameState_t& state) {
    uint16_t count_projectiles = state.map_projectiles.size();
    send_2_bytes(count_projectiles);
    for (Projectiles_t projectile: state.map_projectiles) {
        send_byte(projectile.texture_id);  // texture_id
        send_coordinates(projectile.coordinate);
        send_byte(static_cast<uint8_t>(projectile.direction));
    }
}



void ProtocolServer::send_boxes_state(GameState_t& state) {
    uint8_t count_boxes = state.map_boxes.size();
    send_byte(count_boxes);  //
    for (Box_t box: state.map_boxes) {
        send_byte(box.texture_id);               // texture_id
        send_coordinates(box.coordinate);        // posicion del escenario
        send_byte(box.frame);                    // frame
    }
}

void ProtocolServer::send_scenario_state(GameState_t& state) {
    uint8_t count_map_items = state.map.size();
    send_byte(count_map_items);  //
    for (std::shared_ptr<Positionable> item_map: state.map) {
        send_byte(0);                                 // path
        send_byte(item_map->get_texture_id());        // id_sprite
        send_coordinates(item_map->get_coordinate());
    }
}

void ProtocolServer::send_map_items_state(GameState_t& state) {
    uint8_t count_map_items = state.map_items.size();
    send_byte(count_map_items);
    for (ItemsMap_t item: state.map_items) {
        send_byte(item.texture_id);         // texture_id
        send_coordinates(item.coordinate);  // posicion del escenario
        send_byte(item.frame);              // frame
    }
}

void ProtocolServer::send_statistics_state(GameState_t& state){
    uint8_t rounds = state.statistics.rounds;
    uint8_t id_winer = state.statistics.id_winer;
    //uint8_t rounds = state.statistics.rounds;
    this->send_byte(rounds);
    this->send_byte(id_winer);
}


void ProtocolServer::send_game_state(GameState_t& state) {
    send_byte (static_cast<uint8_t>( state.moment));  
    send_players_state(state);
    send_projectiles_state(state);
    send_boxes_state(state);
    send_scenario_state(state);
    send_map_items_state(state);
    send_statistics_state(state);
}

uint8_t ProtocolServer::receive_count_players() {
    uint8_t count_players = 0;
    receive_byte(count_players);
    return count_players;
}


void ProtocolServer::send_new_player(const uint8_t& sender) { this->send_byte(sender); }

void ProtocolServer::send_count_players(const uint8_t& sender) { this->send_2_bytes(sender); }

void ProtocolServer::receive_event(uint8_t& player_id, ActionEvent& event_id) {
    uint8_t code_client = 0;
    receive_byte(code_client);
    if (code_client == BYTE_CLIENT) {
        receive_byte(player_id);
        uint8_t event_id_byte = 0;
        receive_byte(event_id_byte);
        event_id = static_cast<ActionEvent>(event_id_byte);
    }
}


ProtocolServer::~ProtocolServer() {}
