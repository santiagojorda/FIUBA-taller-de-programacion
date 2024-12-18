#include "circular_counter.h"



CircularCounter::CircularCounter(const int& _range) : range(_range), count(_range) {}

bool   CircularCounter::operator()(){
    auto lap =  !(this->count % this->range);
    this->count++;
    return lap;
}

void CircularCounter::reset_count() { this->count = this->range; }

CircularCounter::~CircularCounter() {}







