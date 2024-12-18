#include "frameable.h"

Frameable::Frameable(const uint8_t& _max_frames) : frame(0), max_frames(_max_frames) {}

void Frameable::reset() { frame = 0;}

void Frameable::increment_frame() {
    if(frame < max_frames - 1){
        frame++;
    }
}

bool Frameable::has_reached_max_frames() const { return frame == max_frames - 1; }

uint8_t Frameable::get_frame() {return frame;}
uint8_t Frameable::get_max_frames() {return max_frames;}
Frameable::~Frameable() {}