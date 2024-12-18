#ifndef MAP_DESERIALIZE_H
#define MAP_DESERIALIZE_H

#include <list>
#include <utility>
#include <vector>
#include "../game/list_boxes.h"

#include <yaml-cpp/yaml.h>

#include "../../common/coordinate.h"
#include "../map/map.h"

struct data_item {
    uint8_t id;
    Coordinate coordinate;
};



class MapDeserialize {
private:
    YAML::Node map;
public:
    explicit MapDeserialize(const std::string& path);

    void load_floors(Map& charge_map);
    void load_boxes(std::list<data_item>& data_items);
    void load_helmets(std::list<data_item>& data_items);
    void load_armors(std::list<data_item>& data_items);

    void load_inicial_points(std::vector<Coordinate>& points);
    void load_weapons(std::list<data_item>& data_items);


    ~MapDeserialize();
};


#endif  // MAP_DESERIALIZE_H
