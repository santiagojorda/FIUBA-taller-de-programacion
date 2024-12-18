#include "common_duck.h"

#include "common_shop_item.h"

Duck::Duck(): primary(), secondary(), knife() {}

void Duck::equip_knife() { knife.equip(); }

void Duck::unequip_knife() { knife.unequip(); }

bool Duck::has_primary_weapon() { return primary.is_equipped(); }

bool Duck::has_secondary_weapon() { return secondary.is_equipped(); }

bool Duck::has_equipped_knife() { return knife.is_equipped(); }

uint8_t Duck::get_primary_ammo() { return primary.get_ammo(); }

uint8_t Duck::get_secondary_ammo() { return secondary.get_ammo(); }

Knife Duck::get_knife() { return knife; }

Weapon Duck::get_primary_weapon() { return primary; }

Weapon Duck::get_secondary_weapon() { return secondary; }

void Duck::add_primary_ammo(uint8_t new_ammo) {
    if (has_primary_weapon())
        primary.add_ammo(new_ammo);
}

void Duck::add_secondary_ammo(uint8_t new_ammo) {
    if (has_secondary_weapon())
        secondary.add_ammo(new_ammo);
}

void Duck::set_primary_weapon(const Weapon& new_weapon) { primary = new_weapon; }

void Duck::set_secondary_weapon(const Weapon& new_weapon) { secondary = new_weapon; }

void Duck::toggle_knife() {
    if (has_equipped_knife())
        unequip_knife();
    else
        equip_knife();
}
