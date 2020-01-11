#pragma once

#include "Point.h"
#include <iostream>
#include <exception>

template <typename T>
class Trapeze {
public:
    Trapeze() = default;
    Trapeze(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    void Print(std::ostream& os) const;
    void Scan(std::istream& is);
    Point<T> Center() const;
    double Area() const;

private:
    Point<T> p1_, p2_, p3_, p4_;
};

template <typename T>
Trapeze<T>::Trapeze(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4)
        :  p1_(p1), p2_(p2), p3_(p3), p4_(p4){
    Vector v1(p1_, p2_), v2(p3_, p4_);
    if (v1 = Vector(p1_, p2_), v2 = Vector(p3_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p3_, p4_);
        }
    } else if (v1 = Vector(p1_, p3_), v2 = Vector(p2_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p4_);
        }
        std::swap(p2_, p3_);
    } else if (v1 = Vector(p1_, p4_), v2 = Vector(p2_, p3_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p3_);
        }
        std::swap(p2_, p4_);
        std::swap(p3_, p4_);
    } else {
        throw std::logic_error("At least 2 sides of trapeze must be parallel");
    }

}

template <typename T>
Point<T> Trapeze<T>::Center() const {
    return (p1_ + p2_ + p3_ + p4_)/4;
}

template <typename T>
double Trapeze<T>::Area() const {
    double A = p2_.y - p3_.y;
    double B = p3_.x - p2_.x;
    double C = p2_.x*p3_.y - p3_.x*p2_.y;
    double height = (std::abs(A*p1_.x + B*p1_.y + C) / sqrt(A*A + B*B));
    return (Vector<T>(p1_, p2_).length() + Vector<T>(p3_, p4_).length()) * height / 2;
}

template <typename T>
void Trapeze<T>::Print(std::ostream& os) const {
    os << "Трапеция, точки - " << "(" << p1_ << ") "
       << "(" << p2_ << ") "
       << "(" << p3_ << ") "
       << "(" << p4_ << ") ";
}

template <typename T>
void Trapeze<T>::Scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Trapeze(p1,p2,p3,p4);
}