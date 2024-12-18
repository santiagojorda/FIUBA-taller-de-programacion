#ifndef INVENTORY
#define INVENTORY

#include "../attributes/equippable.h"

class GameLogic;

class GameLogic;
class Gun;
class Armor;
class Helmet;

class Inventory {
private:
    std::shared_ptr<Gun> gun;
    std::shared_ptr<Armor> armor;
    std::shared_ptr<Helmet> helmet;

public:
    Inventory();
    void equip(std::shared_ptr<Equippable> new_item);
    void equip(std::shared_ptr<Gun> new_gun);
    void equip(std::shared_ptr<Armor> new_armor);
    void equip(std::shared_ptr<Helmet> new_helmet);
    void reset();

    std::shared_ptr<Gun> get_gun();
    std::shared_ptr<Armor> get_armor();
    std::shared_ptr<Helmet> get_helmet();
    void drop_gun(GameLogic& game_logic);
    void drop_armor();
    void drop_helmet();
    // void drop_item(std::shared_ptr<Positionable> item, GamePhysics physics);
    bool has_equipped_this(std::shared_ptr<Equippable> item);

    ~Inventory();
};

#endif
