#include "rectangle.h"

#include <iostream>

int Rectangle::width(const Coordinate& c) const { return c.get_w() - c.get_x(); }
int Rectangle::height(const Coordinate& c) const { return c.get_h() - c.get_y(); }

int Rectangle::get_width() { return points.get_w() - points.get_x(); }
int Rectangle::get_height() { return points.get_h() - points.get_y(); }

Rectangle::Rectangle() {}

Rectangle::Rectangle(Coordinate coordinate):
        points(coordinate.get_x(), coordinate.get_y(), coordinate.get_y() + coordinate.get_h(),
               coordinate.get_x() + coordinate.get_w()) {}

Rectangle::Rectangle(int x_min, int y_min, int x_max, int y_max):
        points(x_min, y_min, x_max, y_max) {}

Rectangle::Rectangle(const Rectangle& _other): Rectangle(_other.get_coordinates()) {}

Rectangle& Rectangle::operator=(const Rectangle& _other) {
    this->points = _other.points;
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const {
    int this_area = width(this->points) * height(this->points);
    int other_area = width(other.points) * height(other.points);

    return this_area == other_area;
}


bool Rectangle::operator<(const Rectangle& other) const {
    int this_area = width(this->points) * height(this->points);
    int other_area = width(other.points) * height(other.points);

    return this_area < other_area;
}


bool Rectangle::operator>(const Rectangle& other) const {
    int this_area = width(this->points) * height(this->points);
    int other_area = width(other.points) * height(other.points);

    return this_area > other_area;
}

bool Rectangle::operator<=(const Rectangle& other) const {
    return this->operator==(other) || this->operator<(other);
}

bool Rectangle::operator>=(const Rectangle& other) const {
    return this->operator==(other) || this->operator>(other);
}

Rectangle Rectangle::operator*(int escale) const {
    return Rectangle(this->points.get_x(), this->points.get_y(),
                     this->points.get_h() + (escale / 2), this->points.get_w() + (escale / 2));
}

Rectangle Rectangle::operator/(int escale) const {
    return Rectangle(this->points.get_x(), this->points.get_y(),
                     this->points.get_h() - (escale / 2), this->points.get_w() - (escale / 2));
}

Coordinate Rectangle::get_points() const { return this->points; }

Coordinate Rectangle::get_coordinates() const {
    int x = this->points.get_x();
    int y = this->points.get_y();
    int h = height(points);
    int w = width(points);
    return Coordinate(x, y, h, w);
}

int Rectangle::get_x_min() const { return this->points.get_x(); }

int Rectangle::get_x_max() const { return this->points.get_w(); }

int Rectangle::get_y_min() const { return this->points.get_y(); }

int Rectangle::get_y_max() const { return this->points.get_h(); }

// void Rectangle::bottom_touch(const Rectangle& bottom_surface){
//     int y_difference = bottom_surface.get_y_min() - get_y_max();
//     std::cout << y_difference << std::endl;
//     int difference_fixed = std::abs(y_difference) - 1;
//     points = points + Coordinate(0, difference_fixed, difference_fixed, 0);;
// }

// bool Rectangle::is_bottom_touching(const Rectangle& bottom_surface){
//     return std::abs(bottom_surface.get_y_min() - get_y_max()) <= 1;
// }


Rectangle::~Rectangle() {}
