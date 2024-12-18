#ifndef STATABLE
#define STATABLE

#include <cstdint>

#include "../../common/rectangle.h"

class Statable {

protected:
    uint8_t initial_state;
    uint8_t state;

public:
    Statable(const uint8_t& _initial_state);
    void set_state(const uint8_t& new_state);
    uint8_t get_state();
    void reset_state();
    virtual ~Statable();
};

#endif
