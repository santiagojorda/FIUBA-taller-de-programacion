#ifndef COMMON_BOX_H
#define COMMON_BOX_H

#include <arpa/inet.h>

class Box {
private:
    // cppcheck-suppress unusedStructMember
    uint8_t id;
    // cppcheck-suppress unusedStructMember
    uint8_t count_iterations_to_appear;
    uint8_t timer = 0;
    bool appeared = true;
    void appear();

public:
    Box();
    explicit Box(const uint8_t id, const uint8_t count_iterations_to_appear);
    bool add_iteration();

    bool is_appeared();
    void pick();
    uint8_t get_id();
};

#endif
