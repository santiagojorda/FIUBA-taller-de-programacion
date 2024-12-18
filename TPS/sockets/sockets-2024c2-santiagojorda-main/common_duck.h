#ifndef DUCK_H
#define DUCK_H

#include <arpa/inet.h>

#include "common_shop_item.h"

#define NOT_EQUIPPED 0
#define EQUIPPED 1
#define NO_AMMO 0

#define ADD_SECONDARY_AMMO 7
#define ADD_PRIMARY_AMMO 10

class Duck {
private:
    Weapon primary;
    Weapon secondary;
    // cppcheck-suppress unusedStructMember
    Knife knife;

public:
    Duck();

    void equip_knife();
    void unequip_knife();

    void set_primary_weapon(const Weapon& new_weapon);
    void set_secondary_weapon(const Weapon& new_weapon);

    void add_primary_ammo(uint8_t new_ammo);
    void add_secondary_ammo(uint8_t new_ammo);

    bool has_primary_weapon();
    bool has_secondary_weapon();
    bool has_equipped_knife();

    Weapon get_primary_weapon();
    Weapon get_secondary_weapon();
    uint8_t get_primary_ammo();
    uint8_t get_secondary_ammo();
    Knife get_knife();

    void toggle_knife();
};

#endif
