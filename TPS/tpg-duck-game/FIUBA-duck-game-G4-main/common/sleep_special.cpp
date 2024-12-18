#include "sleep_special.h"

#include <thread>

SleepSpecial::SleepSpecial(int _rate):
        rate(_rate), chrono_prev(std::chrono::high_resolution_clock::now()) {}

void SleepSpecial::sleep_rate(int& iterations) {
    auto chrono_now = std::chrono::high_resolution_clock::now();
    auto delta_chrono =
            std::chrono::milliseconds(rate) -
            std::chrono::duration_cast<std::chrono::milliseconds>(chrono_now - chrono_prev);

    if (delta_chrono < std::chrono::milliseconds(0)) {
        auto behind = -delta_chrono;
        auto lost = behind - behind % rate;
        chrono_now += lost;
        iterations += std::chrono::duration_cast<std::chrono::milliseconds>(lost / rate).count();
    } else {
        std::this_thread::sleep_for(delta_chrono);
    }
    chrono_prev = chrono_now;
}

void SleepSpecial::sleep_rate() {
    int dumyy = 0;
    this->sleep_rate(dumyy);
}

void SleepSpecial::reset() { chrono_prev = std::chrono::high_resolution_clock::now(); }

void SleepSpecial::sleep(const int& miliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

SleepSpecial::~SleepSpecial() {}
