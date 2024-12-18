#ifndef LIST_GUNS
#define LIST_GUNS

#include "../utils/list_generic.h"

#include "gun.h"

class ListGuns: public ListGeneric<Gun> {

public:
    ListGuns() = default;
    ~ListGuns() = default;
};

#endif