#ifndef DRAWER_H
#define DRAWER_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "../../common/coordinate.h"
#include "../../common/queue.h"
#include "../../common/socket.h"
#include "../../common/state_duck.h"
#include "../animation/animation.h"
#include "../animation/animation_loader.h"
#include "../config/game_config.h"
#include "../game_state/player.h"
#include "../keyboard/keyboard_controller.h"
#include "../protocol/protocol_client.h"
#include "../zoom/zoom_handler.h"

#include "drawer_box.h"
#include "drawer_bullet.h"
#include "drawer_floor.h"
#include "drawer_player.h"
#include "drawer_weapon.h"

struct drawers_t {
    std::vector<DrawerPlayer*> players;
    std::vector<DrawerFloor*> floors;
    std::vector<DrawerWeapon*> weapons;
    std::vector<DrawerBox*> boxes;
    std::vector<DrawerBullet*> bullets;
};

struct animations_t {
    std::map<std::string, Animation> animation_duck;
    std::map<std::string, Animation> animation_weapon;
    std::map<std::string, Animation> animation_armor;
    std::map<std::string, Animation> animation_boxes;
    std::map<std::string, Animation> animation_bullets;
};

class Drawer {
private:
    Queue<ClientEvent_t>& commands;
    Queue<client_game_state_t>& game_state;
    KeyboardController keyboard_controller;
    drawers_t drawers;
    animations_t animations;
    client_game_state_t actual_game_state;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    void load_ducks();

    void load_floor();

    void load_weapons();

    void load_boxes();

    void load_bullets();

    void clean_elements();

    void update_zoom(ZoomHandler& zoom_handler, SDL2pp::Texture& main_texture);

public:
    /*
     * Constructor.
     */
    Drawer(Queue<ClientEvent_t>& commands, Queue<client_game_state_t>& game_state);

    /*
     *
     */
    void run();

    /*
     *
     */
    void load_resources();

    void init_scenery(const client_game_state_t& actual_game_state);

    /*
     * Deshabilitar copias.
     */
    Drawer(const Drawer&) = delete;
    Drawer& operator=(const Drawer&) = delete;
};

#endif  // DRAWER_H
