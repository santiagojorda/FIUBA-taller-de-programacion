#ifndef FRAMEABLE_H
#define FRAMEABLE_H

#include <cstdint>

class Frameable{
protected:
    uint8_t frame;
    uint8_t max_frames;

public:
    explicit Frameable(const uint8_t& _max_frames);

    void increment_frame();

    bool has_reached_max_frames() const;

    void reset();

    uint8_t get_frame();
    uint8_t get_max_frames();

    virtual ~Frameable();
};

#endif
