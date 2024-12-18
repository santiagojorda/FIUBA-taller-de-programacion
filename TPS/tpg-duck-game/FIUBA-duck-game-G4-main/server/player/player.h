#ifndef SERVER_PLAYER_H_
#define SERVER_PLAYER_H_

#include <cstdint>

#include "../../common/direction.h"
#include "../attributes/equippable.h"
#include "../attributes/positionable.h"
#include "../game/game_logic.h"
#include "inventory.h"
#include "../weapons/gun.h"
#include "../attributes/collidable.h"

// #include "duck_state_controller.h"3
#include "duck_state_controller.h"
#include "../weapons/mode_shoot.h"

class GameLogic;
class ListProjectiles;
class Ground;
class Projectile;

class Player: public Positionable, public Collidable {
private:
    // cppcheck-suppress unusedStructMember
    uint8_t health;  // te lo dejo para ir pensado en la vida
    Inventory inventory;
    DuckStateController state;
    void log_action(const std::string& action);
    void update_gun_position();

public:
    explicit Player(uint8_t _id);
    Player& operator=(const Player& _other);
    uint8_t get_id() const;
    void adjust_position_to_floor(std::shared_ptr<Positionable> floor);
    void translate_x(int pasos) override;
    void translate_y(int pasos) override;
    void recoil(GameLogic& game_logic);
    Coordinate get_coordinates_collisionables();
    std::shared_ptr<Gun> get_gun();
    std::shared_ptr<Armor> get_armor();
    std::shared_ptr<Helmet> get_helmet();

    void shoot(GameLogic& game_logic, const   ModeShoot&  mode);

    void equip(std::shared_ptr<Equippable> item);
    Direction get_direction();
    Inventory& get_inventory();
    
    void reset();

    void update(GameLogic& game_logic);
    void run_right(GameLogic& game_logic);
    void run_left(GameLogic& game_logic);
    void jump();
    bool is_slipping();
    void fall(GameLogic& game_logic) override;
    void crouch();
    void slip();
    // void plane(GameLogic& game_logic);
    void die(GameLogic& game_logi);
    void idle();

    using Collidable::on_collision_with;
    void on_collision_with(std::shared_ptr<Equippable> item, GameLogic& game_logic) override;
    void handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) override;


    void drop_gun(GameLogic& game_logic);
    void drop_armor();
    void drop_helmet();

    bool is_jumping();
    bool is_running();
    bool is_falling();
    bool is_idle();
    bool is_dead() const;
    bool is_alive();
    bool is_touching_floor();
    void set_touching_floor(const bool& touch_floor);
    void touch_floor();
    void leave_floor();
    bool is_dead_animation_finished() const;
    bool has_equipped_this(std::shared_ptr<Equippable> item);
    DuckStateType get_state();
    uint8_t get_frame();

    void take_damage(GameLogic& game_logic);

    virtual ~Player();
};

#endif  // SERVER_PLAYER_H_
