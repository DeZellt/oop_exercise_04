#pragma once

#include "Point.h"

template <typename T>
class Rectangle {
public:
    using point_type = T;
    Rectangle() = default;
    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Point<T> Center() const;
    virtual void Scan(std::istream& is);
    void Print(std::ostream& os) const;
    double Area() const;

private:
    Point<T> p1_, p2_, p3_, p4_;
};

template <typename T>
Rectangle<T>::Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4)
        : p1_(p1), p2_(p2), p3_(p3), p4_(p4){
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
        throw std::logic_error("Это не прямоугольник, стороны не перпендикулярны");
    }
    double s1 = Vector(p1_, p2_).length();
    double s2 = Vector(p3_, p4_).length();
    double s3 = Vector(p1_, p3_).length();
    double s4 = Vector(p2_, p4_).length();

    if (!(s1 == s2 && s3 == s4)) {
        throw std::logic_error("Это не прямоугольник, соответствующие стороны не равны");
    }
}

template <typename T>
double Rectangle<T>::Area() const {
    return Vector(p1_,p3_).length() * Vector(p1_,p2_).length();
}

template <typename T>
Point<T> Rectangle<T>::Center() const {
    return (p1_ + p2_ + p3_ + p4_) / 4;
}

template <typename T>
void Rectangle<T>::Print(std::ostream& os) const {
    os << "Прямоугольник, точки - " << "(" << p1_ << ") "
       << "(" << p2_ << ") "
       << "(" << p3_ << ") "
       << "(" << p4_ << ") ";
}

template <typename T>
void Rectangle<T>::Scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Rectangle(p1,p2,p3,p4);
}