#ifndef LIST_ITEMS_MAP_H
#define LIST_ITEMS_MAP_H

#include <vector>
#include <memory>
#include <algorithm>

#include "../attributes/equippable.h"

class ListItemsMap: public std::vector<std::shared_ptr<Equippable>>{

public:
    ListItemsMap() = default;
    void remove_item(std::shared_ptr<Equippable> item){
        auto it = std::find(begin(), end(), item);

        if (it != end()) {
            erase(it);
        }
    }

    ~ListItemsMap() = default;
};

#endif