#include "inventory.h"

#include "../equipment/armor.h"
#include "../equipment/helmet.h"
#include "../weapons/gun.h"
#include "../game/game_logic.h"

Inventory::Inventory(): gun(nullptr), armor(nullptr), helmet(nullptr) {}

void Inventory::equip(std::shared_ptr<Equippable> new_item) { new_item->handle_equip(*this); }

void Inventory::equip(std::shared_ptr<Gun> new_gun) {
    if (!gun) {
        gun = std::move(new_gun);
    }
}

void Inventory::equip(std::shared_ptr<Armor> new_armor) {
    if (!armor) {
        armor = std::move(new_armor);
    }
}

void Inventory::equip(std::shared_ptr<Helmet> new_helmet) {
    if (!helmet) {
        helmet = std::move(new_helmet);
    }
}

void Inventory::reset(){
    this->gun.reset();
    this->helmet.reset();
    this->armor.reset();
}


std::shared_ptr<Gun> Inventory::get_gun() { return gun; }
std::shared_ptr<Armor> Inventory::get_armor() { return armor; }
std::shared_ptr<Helmet> Inventory::get_helmet() { return helmet; }

bool Inventory::has_equipped_this(std::shared_ptr<Equippable> item){
    return (item.get() == gun.get() || item.get() == helmet.get() || item.get() == armor.get()); 
}

void Inventory::drop_gun(GameLogic& game_logic){ 
    if(gun){
        game_logic.handle_drop(gun);
        gun.reset();
    }
}
void Inventory::drop_armor(){ armor.reset();}
void Inventory::drop_helmet(){ helmet.reset(); }


// void Inventory::drop_item(std::shared_ptr<Positionable> item, GamePhysics game_logic){
//     if(item){
//         game_logic.handle_drop(item);
//         item.reset();
//     }
//     else{
//         (void)game_logic;
//     }
// }

Inventory::~Inventory() {
}