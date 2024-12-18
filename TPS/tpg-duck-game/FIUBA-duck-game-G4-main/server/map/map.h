#ifndef MAP
#define MAP

#include <list>
#include <memory>
#include "../attributes/positionable.h"

class Map: public std::list<std::shared_ptr<Positionable>> {
private:
public:
    Map() {}
    void add(std::shared_ptr<Positionable> map_item) { this->push_back(map_item); }
    void remove(std::shared_ptr<Positionable> map_item) { (void)map_item; };

    ~Map() { 
        clear(); 
    }
};

#endif
