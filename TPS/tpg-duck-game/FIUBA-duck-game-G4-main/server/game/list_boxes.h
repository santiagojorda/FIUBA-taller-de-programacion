#ifndef LIST_BOXES_H
#define LIST_BOXES_H

#include <vector>
#include <memory>
#include <algorithm>

#include "../map/box.h"

class ListBoxes: public std::list<std::shared_ptr<Box>>{

public:
    ListBoxes() = default;
    // void remove_item(Box& item){
    //     auto it = std::find(begin(), end(), item);

    //     if (it != end()) {
    //         erase(it);
    //     }
    // }

    ~ListBoxes() = default;
};

#endif