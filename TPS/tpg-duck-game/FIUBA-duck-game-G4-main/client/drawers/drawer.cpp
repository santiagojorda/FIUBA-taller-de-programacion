#include "drawer.h"

#include "../../common/sleep_special.h"

#include "drawer_text.h"

using namespace SDL2pp;

Drawer::Drawer(Queue<ClientEvent_t>& commands, Queue<client_game_state_t>& game_state):
        commands(commands),
        game_state(game_state),
        keyboard_controller(commands, 2),
        drawers(),
        animations(),
        actual_game_state(),
        window(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
               WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED) {}

void Drawer::run() try {
    SDL sdl(SDL_INIT_VIDEO);
    Texture main_texture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH,
                         WINDOW_HEIGHT);
    DrawerText drewer_text;
    main_texture.SetBlendMode(SDL_BLENDMODE_BLEND);

    Texture background(renderer, DATA_PATH "/background.png");

    SleepSpecial sleep(MILISECONDS_30_FPS);
    int iteration = 0;

    ZoomHandler zoom_handler;

    load_resources();
    static std::map<std::string, Animation> empty_animations;

    // ---------------------------- Iniciar partida primer escenario ----------------------------
    // Mientras no reciba un primer escenario, queda en el ciclo


    // -----------------------------------------------------------------------------------------
    while (true) {
        while (game_state.try_pop(actual_game_state)) {}
        this->renderer.Clear();
        this->renderer.Copy(background, Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
        SDL_SetRenderTarget(renderer.Get(), main_texture.Get());
        this->renderer.SetDrawColor(0, 0, 0, 0);
        this->renderer.Clear();
        load_floor();
        load_ducks();
        load_boxes();
        load_weapons();
        load_bullets();
        SDL_SetRenderTarget(this->renderer.Get(), nullptr);
        update_zoom(zoom_handler, main_texture);

        if (actual_game_state.moment == GameMoment::DISPLAY_INFO) {
            std::string winner_text =
                    "Player-" + std::to_string((int)actual_game_state.statistics.id_winer) +
                    "  win: " + std::to_string((int)actual_game_state.statistics.rounds);
            drewer_text.draw(renderer, winner_text);
        }
        if (actual_game_state.moment == GameMoment::FINISHED) {
            drewer_text.draw(renderer, "GAME END");
        }
        this->renderer.Present();

        sleep.sleep_rate(iteration);
        SDL_Event event;
        keyboard_controller.procesar_comando(event);
    }

    clean_elements();
} catch (std::exception& e) {
    clean_elements();
    std::cerr << e.what() << std::endl;
}

void Drawer::load_ducks() {
    if (actual_game_state.players.size() != drawers.players.size()) {
        drawers.players.resize(actual_game_state.players.size());

        for (size_t i = 0; i < actual_game_state.players.size(); i++) {
            auto player = actual_game_state.players[i];
            DrawerPlayer* new_player = new DrawerPlayer(
                    this->renderer, player.sprite.id_texture, this->animations.animation_duck,
                    this->animations.animation_weapon, this->animations.animation_armor);
            drawers.players[i] = new_player;
        }
    }

    for (size_t i = 0; i < actual_game_state.players.size(); i++) {
        player_t player = actual_game_state.players[i];
        drawers.players[i]->draw(player);
    }
}

void Drawer::load_floor() {
    if (drawers.floors.size() != actual_game_state.floors.size()) {
        drawers.floors.resize(actual_game_state.floors.size());

        for (size_t i = 0; i < actual_game_state.floors.size(); ++i) {
            if (!drawers.floors[i]) {
                auto floor = actual_game_state.floors[i];
                DrawerFloor* drawer_floor = new DrawerFloor(this->renderer, floor.path);
                drawers.floors[i] = drawer_floor;
            }
        }
    }

    for (size_t i = 0; i < actual_game_state.floors.size(); ++i) {
        auto floor = actual_game_state.floors[i];
        drawers.floors[i]->draw(floor);
    }
}

void Drawer::load_weapons() {
    if (drawers.weapons.empty() && actual_game_state.weapons.empty()) {
        return;
    }

    for (auto& weapon: drawers.weapons) {
        delete weapon;
    }

    drawers.weapons.clear();
    drawers.weapons.resize(actual_game_state.weapons.size());

    for (size_t i = 0; i < actual_game_state.weapons.size(); ++i) {
        auto weapon = actual_game_state.weapons[i];
        DrawerWeapon* drawer_weapon = new DrawerWeapon(this->renderer, weapon.sprite.id_texture,
                                                       animations.animation_weapon);
        drawers.weapons[i] = drawer_weapon;
    }

    for (size_t i = 0; i < actual_game_state.weapons.size(); ++i) {
        auto weapon = actual_game_state.weapons[i];
        drawers.weapons[i]->draw(weapon);
    }
}

void Drawer::load_boxes() {
    if (drawers.boxes.empty() && actual_game_state.boxs.empty()) {
        return;
    }

    for (auto& box: drawers.boxes) {
        delete box;
    }

    drawers.boxes.clear();
    drawers.boxes.resize(actual_game_state.boxs.size());
    for (size_t i = 0; i < actual_game_state.boxs.size(); ++i) {
        auto box = actual_game_state.boxs[i];
        DrawerBox* drawer_box =
                new DrawerBox(this->renderer, box.box.id_texture, animations.animation_boxes);
        drawers.boxes[i] = drawer_box;
    }

    for (size_t i = 0; i < actual_game_state.boxs.size(); ++i) {
        auto box = actual_game_state.boxs[i];
        drawers.boxes[i]->draw(box);
    }
}

void Drawer::load_bullets() {
    if (drawers.bullets.empty() && actual_game_state.bullets.empty()) {
        return;
    }

    for (auto& bullet: drawers.bullets) {
        delete bullet;
    }

    drawers.bullets.resize(actual_game_state.bullets.size());
    for (size_t i = 0; i < actual_game_state.bullets.size(); ++i) {
        auto bullet = actual_game_state.bullets[i];
        DrawerBullet* drawer_bullet = new DrawerBullet(this->renderer, bullet.bullet.id_texture,
                                                       animations.animation_bullets);
        drawers.bullets[i] = drawer_bullet;
    }

    for (size_t i = 0; i < actual_game_state.bullets.size(); ++i) {
        auto bullet = actual_game_state.bullets[i];
        drawers.bullets[i]->draw(bullet);
    }
}

void Drawer::clean_elements() {
    for (size_t i = 0; i < actual_game_state.players.size(); i++) {
        delete drawers.players[i];
    }

    for (size_t i = 0; i < actual_game_state.floors.size(); i++) {
        delete drawers.floors[i];
    }

    for (size_t i = 0; i < actual_game_state.weapons.size(); i++) {
        delete drawers.weapons[i];
    }

    for (size_t i = 0; i < actual_game_state.boxs.size(); i++) {
        delete drawers.boxes[i];
    }

    for (size_t i = 0; i < actual_game_state.bullets.size(); i++) {
        delete drawers.bullets[i];
    }
}

void Drawer::init_scenery(const client_game_state_t& actual_game_state) {
    if (actual_game_state.players.size() == drawers.players.size()) {
        return;
    }

    drawers.players.resize(actual_game_state.players.size());

    for (size_t i = 0; i < actual_game_state.players.size(); i++) {
        auto player = actual_game_state.players[i];

        DrawerPlayer* new_player = new DrawerPlayer(
                this->renderer, player.sprite.id_texture, this->animations.animation_duck,
                this->animations.animation_weapon, this->animations.animation_armor);
        drawers.players[i] = new_player;
    }
}

void Drawer::load_resources() {
    AnimationLoader::load_animations(ANIMATION_PATH DUCK_FILE, animations.animation_duck);
    AnimationLoader::load_animations(ANIMATION_PATH WEAPON_FILE, animations.animation_weapon);
    AnimationLoader::load_animations(ANIMATION_PATH ARMOR_FILE, animations.animation_armor);
    AnimationLoader::load_animations(ANIMATION_PATH BOX_FILE, animations.animation_boxes);
    AnimationLoader::load_animations(ANIMATION_PATH BULLET_FILE, animations.animation_bullets);
}

void Drawer::update_zoom(ZoomHandler& zoom_handler, SDL2pp::Texture& main_texture) {
    if (actual_game_state.players.size() > 0) {
        zoom_handler.calculate_zoom(actual_game_state.players);
        zoom_handler.apply_zoom(this->renderer, main_texture);
    }
}
