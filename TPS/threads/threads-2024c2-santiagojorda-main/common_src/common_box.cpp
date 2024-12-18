#include "common_box.h"

Box::Box() {}

Box::Box(const uint8_t id, const uint8_t count_iterations_to_appear):
        id(id), count_iterations_to_appear(count_iterations_to_appear) {}

bool Box::add_iteration() {
    ++timer;
    if (timer == count_iterations_to_appear) {
        appear();
        return true;
    }
    return false;
}

void Box::pick() {
    timer = 0;
    appeared = false;
}

void Box::appear() {
    appeared = true;
    timer = 0;
}

bool Box::is_appeared() { return appeared; }

uint8_t Box::get_id() { return id; }
