#include "server_game_logic.h"

#define BOX_ID_01 0x01
#define BOX_ID_02 0x02
#define BOX_ID_03 0x03
#define BOX_ID_04 0x04

#define NO_REWARD 0x00
#define REWARD_ID_01 0x10
#define REWARD_ID_02 0x11
#define REWARD_ID_03 0x12
#define REWARD_ID_04 0x13

GameLogic::GameLogic() {
    Box box1(1, 15);
    Box box2(2, 5);
    Box box3(3, 20);
    Box box4(4, 10);

    boxes.push_back(box1);
    boxes.push_back(box2);
    boxes.push_back(box3);
    boxes.push_back(box4);
}

void GameLogic::add_iteration(uint8_t& count_boxes_appeared) {
    count_boxes_appeared = 0;
    bool box_appeared;

    for (Box& box: boxes) {
        if (!box.is_appeared()) {

            box_appeared = box.add_iteration();
            if (box_appeared) {
                count_boxes_appeared++;
            }
        }
    }
}

uint8_t GameLogic::pick(const uint8_t& box_id) {

    // estoy suponiendo que se elije una box_id correcta
    bool is_picked = false;

    for (Box& box_aux: boxes) {
        if (box_aux.get_id() == box_id && box_aux.is_appeared()) {
            box_aux.pick();
            is_picked = true;
            break;
        }
    }

    uint8_t reward_id = NO_REWARD;
    if (is_picked) {
        switch (box_id) {
            case BOX_ID_01:
                reward_id = REWARD_ID_01;
                break;
            case BOX_ID_02:
                reward_id = REWARD_ID_02;
                break;
            case BOX_ID_03:
                reward_id = REWARD_ID_03;
                break;
            case BOX_ID_04:
                reward_id = REWARD_ID_04;
                break;
        }
    }
    return reward_id;
}
