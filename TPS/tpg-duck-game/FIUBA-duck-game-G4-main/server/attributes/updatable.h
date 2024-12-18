#ifndef UPDATABLE_H
#define UPDATABLE_H

#include <cstdint>

class Updatable{
protected:
    uint8_t tick;

public:
    Updatable();

    virtual void update();

    uint8_t get_tick();

    bool is_ready_for_action(const uint8_t& divisor); 

    void reset();

    virtual ~Updatable();
};

#endif
