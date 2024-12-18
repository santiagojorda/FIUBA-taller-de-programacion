#ifndef LIST_PROJECTILES
#define LIST_PROJECTILES

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "projectile.h"

class ListProjectiles: public std::vector<std::shared_ptr<Projectile>> {

public:
    ListProjectiles() = default;
    void remove_item(std::shared_ptr<Projectile>& item){
        auto it = std::find(begin(), end(), item);
        if (it != end()) {
            erase(it);
            std::cout << "se elimino projectil" << std::endl;
        }
    }
    ~ListProjectiles() = default;
};

#endif