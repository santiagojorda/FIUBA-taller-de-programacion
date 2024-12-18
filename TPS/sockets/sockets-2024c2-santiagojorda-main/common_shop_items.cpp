#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "common_shop_item.h"

Item::Item(): name(NOT_EQUIPPED_TEXT), id(NOT_EQUIPPED) {}

Item::Item(uint8_t new_id, const std::string& new_name): name(new_name), id(new_id) {}

uint8_t Item::get_id() { return id; }

std::string Item::get_name() { return name; }

Shop::Shop() {
    std::vector<std::string> aux;
    aux.push_back(BANANA);
    aux.push_back(MAGNUM);
    aux.push_back(OLD_PISTOL);
    aux.push_back(PEW_PEW_LASER);
    aux.push_back(PHASER);
    aux.push_back(CHAINDART);
    aux.push_back(SECONDARY_AMMO);
    aux.push_back(PRIMARY_AMMO);
    aux.push_back(KNIFE);

    for (int i = 0; i < int(aux.size()); i++) {
        items.push_back(Item(i + 1, aux[i]));
    }
}

Weapon Shop::buy_weapon(uint8_t item_id) {
    for (Item item: items) {
        if (item.get_id() == item_id) {
            return Weapon(item);
        }
    }
    // std::cout << "No se encontro item" << std::endl;
    throw std::exception();
}

uint8_t Shop::buy_primary_ammo() { return BUY_PRIMARY_AMMO; }

uint8_t Shop::buy_secondary_ammo() { return BUY_SECONDARY_AMMO; }

Weapon::Weapon(): item(), ammo(NO_AMMO) {}

Weapon::Weapon(const Item& item): item(item), ammo(NO_AMMO) { ammo = NO_AMMO; }

void Weapon::add_ammo(uint8_t new_ammo) { ammo += new_ammo; }

std::string Weapon::get_name() { return item.get_name(); }

uint8_t Weapon::get_ammo() { return ammo; }

bool Weapon::is_equipped() { return item.get_id() != NOT_EQUIPPED; }

uint8_t Knife::is_equipped() { return knife; }

Knife::Knife() {}

void Knife::equip() { knife = EQUIPPED; }

void Knife::unequip() { knife = NOT_EQUIPPED; }
