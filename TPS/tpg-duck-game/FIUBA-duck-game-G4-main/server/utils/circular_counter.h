#ifndef CIRCULAR_COUNTER_H
#define CIRCULAR_COUNTER_H



class CircularCounter{
private:
    int range;
    int count;

public:
    CircularCounter(const int& _range);

    bool operator()();

    void reset_count();

    ~CircularCounter();
};




#endif // CIRCULAR_COUNTER_H

