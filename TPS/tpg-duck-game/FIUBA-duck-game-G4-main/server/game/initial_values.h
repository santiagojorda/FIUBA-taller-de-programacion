#ifndef INITIAL_VALUES_H
#define INITIAL_VALUES_H

#include <vector>
#include <list>
#include "../yamel/map_deserialize.h"

#include "../../common/coordinate.h"

struct inical_values_t{
    std::vector<Coordinate> points;
    std::list<data_item> data_weapons;
    std::list<data_item> data_boxes;
    std::list<data_item> data_armor;
    std::list<data_item> data_helmet;
};





#endif // INITIAL_VALUES_H
