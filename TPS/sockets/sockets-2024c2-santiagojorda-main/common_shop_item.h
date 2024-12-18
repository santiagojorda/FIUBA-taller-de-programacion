#ifndef COMMON_SHOP_ITEMS_H
#define COMMON_SHOP_ITEMS_H

#include <cstdint>
#include <string>
#include <vector>

#define NOT_EQUIPPED_TEXT "Not Equipped"

#define BANANA "Banana"
#define MAGNUM "Magnum"
#define OLD_PISTOL "Old Pistol"
#define PEW_PEW_LASER "Pew Pew Laser"
#define PHASER "Phaser"
#define CHAINDART "Chaindart"
#define SECONDARY_AMMO "Secondary Ammo"
#define PRIMARY_AMMO "Primary Ammo"
#define KNIFE "Knife"

#define NOT_EQUIPPED 0
#define EQUIPPED 1
#define NO_AMMO 0

#define BUY_SECONDARY_AMMO 7
#define BUY_PRIMARY_AMMO 10

class Item {
private:
    // cppcheck-suppress unusedStructMember
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t id;

public:
    Item();
    explicit Item(uint8_t new_id, const std::string& new_name);
    uint8_t get_id();
    std::string get_name();
};

class Weapon {
private:
    Item item;
    // cppcheck-suppress unusedStructMember
    uint8_t ammo;

public:
    explicit Weapon(const Item& item);
    Weapon();
    void add_ammo(uint8_t new_ammo);
    uint8_t get_ammo();
    bool is_equipped();
    std::string get_name();
};

class Knife {
private:
    uint8_t knife = NOT_EQUIPPED;

public:
    Knife();
    uint8_t is_equipped();
    void equip();
    void unequip();
};

class Shop {
private:
    // cppcheck-suppress unusedStructMember
    std::vector<Item> items;

public:
    Shop();
    Weapon buy_weapon(uint8_t item_id);
    uint8_t buy_primary_ammo();
    uint8_t buy_secondary_ammo();
};


#endif
