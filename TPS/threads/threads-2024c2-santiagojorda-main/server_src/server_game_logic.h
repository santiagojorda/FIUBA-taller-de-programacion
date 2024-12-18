#ifndef SERVER_GAME_LOGIC_H
#define SERVER_GAME_LOGIC_H

#include <vector>

#include <arpa/inet.h>

#include "../common_src/common_box.h"

class GameLogic {

private:
    // cppcheck-suppress unusedStructMember
    std::vector<Box> boxes;
    Box get_box_by_id(uint8_t& box_id);

public:
    GameLogic();
    void add_iteration(uint8_t& count_boxes_appeared);
    uint8_t pick(const uint8_t& box_id);
};

#endif
