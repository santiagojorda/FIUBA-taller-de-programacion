#include "state_duck.h"

// se agrego la cantidad de ticks por frame

std::unordered_map<DuckStateType, DuckStateInfo_t> duck_state_frames = {
        {DuckStateType::JUMPING, {6}},   {DuckStateType::RUNNING, {6}},
        {DuckStateType::CROUCHING, {1}}, {DuckStateType::RECOILING, {3}},
        {DuckStateType::FALLING, {1}},   {DuckStateType::SLIPPING, {2}},
        {DuckStateType::PLANNING, {6}},  {DuckStateType::IDLE, {1}},
        {DuckStateType::DEAD, {8}},      {DuckStateType::AERO_RUNNING, {1}}};
