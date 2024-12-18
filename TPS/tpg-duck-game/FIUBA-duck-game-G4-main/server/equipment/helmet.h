#ifndef HELMET_H
#define HELMET_H

#include "../attributes/equippable.h"
#include "../../common/weapons_id.h"

class Helmet: public Equippable {
public:
    Helmet() : Equippable((uint8_t)WeaponTextureID::HELMET){}
    Helmet(const Coordinate& _coordinate) : Equippable((uint8_t)WeaponTextureID::HELMET, _coordinate) {}

    void handle_equip(Inventory& inventory) override { inventory.equip(std::shared_ptr<Helmet>(this)); }
    std::shared_ptr<Equippable> clone() const {
            return std::make_shared<Helmet>(*this); 
    }

    
};

#endif
