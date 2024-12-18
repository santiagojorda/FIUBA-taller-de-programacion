#include "updatable.h"

Updatable::Updatable() : tick(0){}

void Updatable::update(){ }
uint8_t Updatable::get_tick() { return tick; }
bool Updatable::is_ready_for_action(const uint8_t& divisor){ return tick % divisor == 0;};
void Updatable::reset() { tick = 0; }

Updatable::~Updatable() {}