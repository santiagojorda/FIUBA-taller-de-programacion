#ifndef SLEEP_SPECIAL_H
#define SLEEP_SPECIAL_H

#include <chrono>

class SleepSpecial {
private:
    int rate;
    std::chrono::time_point<std::chrono::high_resolution_clock> chrono_prev;

public:
    SleepSpecial(int _rate);

    void sleep_rate(int& iterations);

    void sleep_rate();
    void reset();
    void sleep(const int& miliseconds);

    ~SleepSpecial();
};


#endif  // SLEEP_SPECIAL_H
