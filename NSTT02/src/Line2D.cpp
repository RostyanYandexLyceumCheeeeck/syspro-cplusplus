#include <iostream>
#include <cmath>

#include "headers/Line2D.h"


Line2D::Line2D(double a, double b, double c) : a_(a), b_(b), c_(c) {}

Line2D::Line2D(const Point2D& p1, const Point2D& p2) {
    double a = p2.x() - p1.x();         //      (x - x0)     (y - y0)
    double b = p2.y() - p1.y();         //      --------  =  --------  it`s canonical equation Line2D <=>
                                        //         a            b             

    a_ = b;                             // <=>  (x - x0)*b = (y - y0)*a         <=>
    b_ = -a;                            // <=>  b*x - a*y + (a*y0 - b*x0) = 0   <=>
    c_ = a*p1.y() - b*p1.x();           //      ||    ||          ||
}                                       // <=>  A*x + B*y +       C       = 0

                                        //      (x  - x1)     (y  - y1)   
                                        //      ---------  =  --------- it`s canonical equation Line2D to two Point2D
                                        //      (x2 - x1)     (y2 - y1)

std::optional<Line2D> Line2D::createLine(double a, double b, double c) {
    if (std::abs(a) < EPS && std::abs(b) < EPS) {
        return std::nullopt;
    }
    return Line2D(a, b, c);
}

std::optional<Line2D> Line2D::createLine(const Point2D& p1, const Point2D& p2) {
    if (std::abs(p1.x() - p2.x()) < EPS && std::abs(p1.y() - p2.y()) < EPS) {
        return std::nullopt;
    }
    return Line2D(p1, p2);
}


double Line2D::a() const { return a_; }
double Line2D::b() const { return b_; }
double Line2D::c() const { return c_; }

std::optional<Point2D> Line2D::intersection(const Line2D& l) const {
    double al = l.a_, bl = l.b_, cl = l.c_;             // { a1*x + b1*y + c1 = 0
    double D = a_*bl -  b_*al;                          // { a2*x + b2*y + c2 = 0

    if (std::abs(D) < EPS) { return std::nullopt; }     // D = |a1 b1|
    return Point2D(                                     //     |a2 b2|  
        (b_*cl - c_*bl)/D,  
        (a_*cl - c_*al)/D                               //     |b1 c1|      |a1 c1|
        );                                              //     |b2 c2|      |a2 c2|
                                                        // x = -------  y = ------- 
}                                                       //        D            D

std::optional<Line2D> Line2D::perpendicular(const Point2D& p) const {
    return Line2D::createLine(a_, b_, -(p.x()*a_ + p.y()*b_));
}

bool Line2D::checkParallelizm(const Line2D& l) const {
    return std::abs(a_*l.b_ - b_*l.a_) < EPS;   // A1   B1 
}                                               // -- = -- <=> A1*B2 = B1*A2
                                                // A2   B2 

bool Line2D::checkCoincidence(const Line2D& l) const {
    return (checkParallelizm(l) &&              // A1   B1   C1
           std::abs(a_*l.c_ - c_*l.a_) < EPS);  // -- = -- = -- <=> A1*B2 = B1*A2 && A1*C2 = A2*C1
}                                               // A2   B2   C2
