#pragma once

#include <iostream>
#include "Point.h"

template <typename T>
class Square {
public:
  using point_type = T;
    Square() = default;
    Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Point<T> Center() const;
    void Scan(std::istream& is);
    void Print(std::ostream& os) const;
    double Area() const;

private:
    Point<T> p1_, p2_, p3_, p4_;
};

template <typename T>
Square<T>::Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4)
        : p1_(p1), p2_(p2), p3_(p3), p4_(p4) {
    if (is_perpendecular(Vector(p1_, p2_), Vector(p1_,p3_))
        && is_perpendecular(Vector(p4_, p2_), Vector(p4_,p3_))
        && is_perpendecular(Vector(p1_, p3_), Vector(p3_,p4_))
        && is_perpendecular(Vector(p1_, p2_), Vector(p2_,p4_))) {

    } else if (is_perpendecular(Vector(p1_, p4_), Vector(p1_,p3_))
               && is_perpendecular(Vector(p2_, p4_), Vector(p2_,p3_))
               && is_perpendecular(Vector(p1_, p3_), Vector(p3_,p2_))
               && is_perpendecular(Vector(p1_, p4_), Vector(p2_,p4_))){
        std::swap(p2_,p4_);
    } else if (is_perpendecular(Vector(p1_, p2_), Vector(p1_,p4_))
               && is_perpendecular(Vector(p3_, p2_), Vector(p3_,p4_))
               && is_perpendecular(Vector(p1_, p2_), Vector(p2_,p3_))
               && is_perpendecular(Vector(p1_, p4_), Vector(p4_,p3_))) {
        std::swap(p3_,p4_);
    } else {
        throw std::logic_error("Это не квадрат, стороны не перпендикулярны");
    }

    double s1 = Vector(p1_, p2_).length();
    double s2 = Vector(p3_, p4_).length();
    double s3 = Vector(p1_, p3_).length();
    double s4 = Vector(p2_, p4_).length();

    if (s1 != s2 || s2 != s3 || s3 != s4 || s4 != s1) {
        throw std::logic_error("Это не квадрат, стороны не равны");
    }
}

template <typename T>
double Square<T>::Area() const {
    return std::pow(Vector(p1_, p2_).length(), 2);
}

template <typename T>
Point<T> Square<T>::Center() const {
    return (p1_ + p2_ + p3_ + p4_) / 4;
}

template <typename T>
void Square<T>::Print(std::ostream& os) const {
    os << "Квадрат, точки - " << "(" << p1_ << ") "
       << "(" << p2_ << ") "
       << "(" << p3_ << ") "
       << "(" << p4_ << ") ";
}

template <typename T>
void Square<T>::Scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Square(p1,p2,p3,p4);
}