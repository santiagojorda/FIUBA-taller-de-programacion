#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "coordinate.h"

class Rectangle {
private:
    Coordinate points;

    int width(const Coordinate& c) const;
    int height(const Coordinate& c) const;

public:
    Rectangle();
    int get_height();
    int get_width();

    /*
    / Inicia con el siguiente formato (x, y , x+w, y+h)
    */
    explicit Rectangle(Coordinate _points);

    Rectangle(int x_min, int y_min, int x_max, int y_max);

    Rectangle(const Rectangle& _other);

    Rectangle& operator=(const Rectangle& _other);

    /*
    /  compara  tamaño de los rectangulos
    */
    bool operator==(const Rectangle& other) const;

    /*
    /  compara  tamaño de los rectangulos
    */
    bool operator<(const Rectangle& other) const;

    /*
    /  compara  tamaño de los rectangulos
    */
    bool operator>(const Rectangle& other) const;

    /*
    /  compara  tamaño de los rectangulos
    */
    bool operator<=(const Rectangle& other) const;

    /*
    /  compara  tamaño de los rectangulos
    */
    bool operator>=(const Rectangle& other) const;

    /*
    /  escala el tamaño del rectangulo
    */
    Rectangle operator*(int escale) const;

    /*
    /  decrece el tamaño del rectangulo
    */
    Rectangle operator/(int decrease) const;

    /*
    /  coordenada en formato (x, y, x+w, y+h)
    */
    Coordinate get_points() const;

    /*
    /  coordenada en formato (x, y, h, w)
    */
    Coordinate get_coordinates() const;

    int get_x_min() const;

    int get_x_max() const;

    int get_y_min() const;

    int get_y_max() const;

    // void bottom_touch(const Rectangle& bottom_surface);
    // bool is_bottom_touching(const Rectangle& bottom_surface);
    ~Rectangle();
};


#endif  // RECTANGLE_H
