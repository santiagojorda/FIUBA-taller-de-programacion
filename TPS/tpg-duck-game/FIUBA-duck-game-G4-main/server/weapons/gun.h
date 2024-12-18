#ifndef GUN
#define GUN

#include <cstdint>

#include "../attributes/directionable.h"
#include "../../common/weapons_id.h"
#include "../attributes/equippable.h"
#include "../attributes/positionable.h"
#include "../player/inventory.h"
#include "../utils/circular_counter.h"

#include "list_projectiles.h"
#include "projectile_range.h"
#include "shooring_recoil.h"

#define INITIAL_DISPERSION 0

enum class GunState: uint8_t {
    DEAD,
    ALIVE,

};

class GameLogic;

struct  gun_config{
    WeaponTextureID id;
    uint8_t max_ammo;
    ShootingRecoil recoil;
    ProjectileRange range;
    uint8_t count_projectiles_x_shoot;
    uint8_t delay_shoot;
};


class Gun: public Equippable, public Directionable{
protected:
    // cppcheck-suppress unusedStructMember
    uint8_t max_ammo;
    // cppcheck-suppress unusedStructMember
    uint8_t ammo;
    // cppcheck-suppress unusedStructMember
    int dispersion;
    ShootingRecoil recoil;
    ProjectileRange projectile_range;
    CircularCounter delay_counter;
    uint8_t tick = 0;
    bool is_waiting_to_explotion = false;

public:

    explicit Gun(const WeaponTextureID& _texture_id, const uint8_t& _max_ammo,
                    const ShootingRecoil& _recoil, const ProjectileRange& _projectile_range,
                    const Coordinate& _coordinate, uint8_t _delay_shoot);
    
    Gun(const gun_config& _config, const Coordinate& _coordinate);
    
    virtual void trigger(ListProjectiles& projectiles, const uint8_t& player_id);

    virtual void trigger_out(ListProjectiles& projectiles, const uint8_t& player_id, bool& was_dropped);

    void handle_equip(Inventory& inventory) override;

    std::shared_ptr<Gun> get_shared_ptr() { return std::dynamic_pointer_cast<Gun>(shared_from_this()); }

    uint8_t get_ammo();
    using Collidable::on_collision_with;
    uint8_t get_max_ammo();
    std::shared_ptr<Equippable> clone() const;
    virtual void handle_explotion(GameLogic& game_logic);

    ShootingRecoil get_recoil();
    virtual ~Gun();
};


#endif
