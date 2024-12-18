#ifndef COMMON_COORDINATE_H_
#define COMMON_COORDINATE_H_

#include <iostream>


class Coordinate {
private:
    // cppcheck-suppress unusedStructMember
    int x;
    // cppcheck-suppress unusedStructMember
    int y;
    // cppcheck-suppress unusedStructMember
    int h;
    // cppcheck-suppress unusedStructMember
    int w;

public:
    Coordinate();

    Coordinate(int _x, int _y, int _h, int _w);

    Coordinate(const Coordinate& _other);

    Coordinate& operator=(const Coordinate& _other);

    // suma componente a componente
    Coordinate operator+(const Coordinate& other) const;

    // sobrescribe  sumando componente a componente
    Coordinate& operator+=(const Coordinate& other);

    // resto componente a componente
    Coordinate operator-(const Coordinate& other) const;

    // sobrescribe restando componente a componente
    Coordinate& operator-=(const Coordinate& other);

    // producto interno de la cordenada
    int operator*(const Coordinate& other) const;

    // multiplica toda la cordenada por el multiplier
    Coordinate operator*(const int& multiplier) const;

    // divide toda la cordenada por el divider
    Coordinate operator/(const int& divider) const;

    bool operator==(const Coordinate& other) const;

    // La norma de la cordenada
    int norm() const;

    // Devuelve el vector unitario de la cordenada
    Coordinate unit_vector();

    int get_x() const;

    int get_y() const;

    int get_h() const;

    int get_w() const;


    friend std::ostream& operator<<(std::ostream& os, const Coordinate& view);

    ~Coordinate();
};


#endif  // COMMON_COORDINATE_H_
