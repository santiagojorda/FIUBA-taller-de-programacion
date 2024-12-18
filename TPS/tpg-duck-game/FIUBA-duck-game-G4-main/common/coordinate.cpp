#include "coordinate.h"

#include <math.h>

Coordinate::Coordinate() {}

Coordinate::Coordinate(int _x, int _y, int _h, int _w): x(_x), y(_y), h(_h), w(_w) {}

Coordinate& Coordinate::operator=(const Coordinate& _other) {
    this->x = _other.x;
    this->y = _other.y;
    this->h = _other.h;
    this->w = _other.w;
    return *this;
}

Coordinate::Coordinate(const Coordinate& _other):
        Coordinate(_other.x, _other.y, _other.h, _other.w) {}


Coordinate Coordinate::operator+(const Coordinate& other) const {
    return Coordinate(this->x + other.x, this->y + other.y, this->h + other.h, this->w + other.w);
}

Coordinate& Coordinate::operator+=(const Coordinate& other) {
    *this = (this->operator+(other));
    return *this;
}

Coordinate Coordinate::operator-(const Coordinate& other) const {
    return Coordinate(this->x - other.x, this->y - other.y, this->h - other.h, this->w - other.w);
}

Coordinate& Coordinate::operator-=(const Coordinate& other) {
    *this = (this->operator-(other));
    return *this;
}

int Coordinate::operator*(const Coordinate& other) const {
    return (this->x * other.x) + (this->y * other.y) + (this->h * other.h) + (this->w * other.w);
}


Coordinate Coordinate::operator*(const int& multiplier) const {
    return Coordinate(this->x * multiplier, this->y * multiplier, this->h * multiplier,
                      this->w * multiplier);
}

Coordinate Coordinate::operator/(const int& divider) const {
    return Coordinate(this->x / divider, this->y / divider, this->h / divider, this->w / divider);
}

bool Coordinate::operator==(const Coordinate& other) const {
    return (this->x == other.x) && (this->y == other.y) && (this->h == other.h) &&
           (this->w == other.w);
}

int Coordinate::norm() const { return sqrt(this->operator*(*this)); }

Coordinate Coordinate::unit_vector() { return (*this) / this->norm(); }

int Coordinate::get_x() const { return this->x; }

int Coordinate::get_y() const { return this->y; }

int Coordinate::get_h() const { return this->h; }

int Coordinate::get_w() const { return this->w; }

std::ostream& operator<<(std::ostream& os, const Coordinate& view) {
    os << "(" << view.get_x() << ", " << view.get_y() << ", " << view.get_h() << ", "
       << view.get_w() << ")";
    return os;
}


Coordinate::~Coordinate() {}
