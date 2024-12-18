#include "statable.h"

Statable::Statable(const uint8_t& _initial_state): 
    initial_state(_initial_state),
    state(_initial_state) 
    {}

void Statable::set_state(const uint8_t& new_state) {
    if (state != new_state) {
        state = new_state;
    }
};

uint8_t Statable::get_state() { return state; };
void Statable::reset_state() {
    state = initial_state;
};
Statable::~Statable() {}