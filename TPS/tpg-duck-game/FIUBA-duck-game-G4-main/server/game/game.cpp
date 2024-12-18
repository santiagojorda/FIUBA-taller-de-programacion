#include "game.h"

#include <iostream>

#include "../../common/sleep_special.h"
#include "../events/event.h"
#include "../weapons/gun_factory.h"
#include "../map/ground.h"
#include "../map/box.h"
#include "../player/player.h"
#include "../yamel/map_deserialize.h"
#include "../equipment/armor.h"
#include "../equipment/helmet.h"

#define MAX_ROUNDS_WINDS 10
#define MILISECONDS_30_FPS 33
#define MILISECONDS_FOR_SECONDS 1000
#define SECONDS_FINISH_GAME 3

Game::Game(ListPlayers& _players, MonitorClients& _monitor_client, QueueEvents& _queue_events,
           QueueGameState& _queue_gamestate,
           const std::string& path_map):
        players(_players),
        map(),
        map_items(),
        map_projectiles(),
        map_boxes(),
        game_logic(players, map, map_items, map_projectiles, map_boxes),
        monitor_client(_monitor_client),
        queue_events(_queue_events),
        queue_gamestate(_queue_gamestate),
        round_manager(players){
    this->load_map(path_map);
}



void charge_ponits(ListPlayers& players, std::vector<Coordinate>& points) {
    int i = 0;
    for (Player& player: players) {
        player.set_coordinate(points[i]);
        i++;
        player.reset();
    }
}

void charge_weapons(ListItemsMap& items, std::list<data_item>& data_items) {
    GunFactory factory;
    for (auto& weapon: data_items) {
        std::shared_ptr<Equippable> new_item = factory.create_gun(weapon.id, weapon.coordinate);
        items.push_back(new_item);
    }
}
void charge_boxes(ListBoxes& items, std::list<data_item>& data_item) {
    for (auto& box: data_item) {
        std::shared_ptr<Box> new_item = std::make_shared<Box>(box.coordinate);
        items.push_back(new_item);
    }
}

void charge_helmets(ListItemsMap& items, std::list<data_item>& data_item) {
    for (auto& helmet: data_item) {
        std::shared_ptr<Helmet> new_item = std::make_shared<Helmet>(helmet.coordinate);
        items.push_back(new_item->clone());
    }
}
void charge_armors(ListItemsMap& items, std::list<data_item>& data_item) {
    for (auto& armor: data_item) {
        std::shared_ptr<Armor> new_item = std::make_shared<Armor>(armor.coordinate);
        items.push_back(new_item->clone());
    }
}

void Game::load_map(const std::string& path_map) {
    try {
        MapDeserialize deserialize(path_map);

        deserialize.load_floors(this->map);
        deserialize.load_boxes(inicial_values.data_boxes);
        deserialize.load_armors(inicial_values.data_armor);
        deserialize.load_helmets(inicial_values.data_helmet);
        deserialize.load_inicial_points(this->inicial_values.points);
        deserialize.load_weapons(this->inicial_values.data_weapons);
        charge_ponits(this->players, this->inicial_values.points);
        charge_weapons(this->map_items, this->inicial_values.data_weapons);
        charge_helmets(this->map_items, this->inicial_values.data_helmet);
        charge_armors(this->map_items, this->inicial_values.data_armor);
        charge_boxes(map_boxes, this->inicial_values.data_boxes);
    } catch (const std::exception& e) {
        std::cerr << "error map.yaml: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unespected error map.yaml" << '\n';
    }
}


void Game::reset_values(){
    this->map_items.clear();
    this->map_projectiles.clear();
    charge_ponits(this->players, this->inicial_values.points);
    charge_weapons(this->map_items, this->inicial_values.data_weapons);
}

void Game::execute_new_events() {
    std::shared_ptr<Event> event = nullptr;
    while (queue_events.try_pop(event)) {
        if (event != nullptr) {
            event->start(game_logic);
        }
    }
}

void Game::broadcast_gamestate() { monitor_client.broadcast(get_gamestate()); }

GameState_t Game::get_gamestate() { 

    std::list<ItemsMap_t> map_items_copy;
    std::list<Projectiles_t> map_projectiles_copy;
    std::list<Box_t> map_boxes_copy;

    for(std::shared_ptr<Equippable> item : map_items){
        map_items_copy.push_back({item->get_texture_id(), item->get_coordinate(), 0});
    }

    for(std::shared_ptr<Projectile> projectile : map_projectiles){
        map_projectiles_copy.push_back({projectile->get_texture_id(), projectile->get_coordinate(), static_cast<uint8_t>( projectile->get_direction())});
    }

    for(std::shared_ptr<Box> box : map_boxes){
        map_boxes_copy.push_back({box->get_texture_id(), box->get_coordinate(), box->get_state()});
    }

    return GameState_t{this->moment, players, map, map_items_copy, map_projectiles_copy, map_boxes_copy, this->round_manager.get_statistics()}; 
}

void Game::display_info(SleepSpecial& sleep){
    this->moment = GameMoment::DISPLAY_INFO;
    this->round_manager.log_state(std::cout, this->get_gamestate());
    broadcast_gamestate();
    sleep.sleep(SECONDS_FINISH_GAME * MILISECONDS_FOR_SECONDS);
    this->reset_values();
    this->round_manager.log_state(std::cout, this->get_gamestate());
    sleep.reset();
}


void Game::run() {
    SleepSpecial sleep(MILISECONDS_30_FPS);

    try {
        while (_keep_running && monitor_client.they_are_alive()) {
            this->moment = GameMoment::IN_GAME;
            execute_new_events();
            game_logic.update();
            broadcast_gamestate();
            sleep.sleep_rate();
            if(this->round_manager.check_winer(this->players)) {
                this->display_info(sleep);
            }
            if(this->round_manager.get_rounds_winer() >= MAX_ROUNDS_WINDS) {
                this->moment = GameMoment::FINISHED;
                broadcast_gamestate();
                sleep.sleep(SECONDS_FINISH_GAME * MILISECONDS_FOR_SECONDS);
                this->stop();
            }
        }
        stop();
        this->round_manager.log_state(std::cout, this->get_gamestate());
    } catch (std::exception& e) {
        std::cout << "Game: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Hubo un error en el game loop" << std::endl;
        stop();
    }
}

void Game::stop() {
    queue_events.close();
    queue_gamestate.close();
    monitor_client.shutdown();
    Thread::stop();
}

Game::~Game() { Thread::~Thread(); }