#include <iostream>

#include "headers/Line2D.h"

Line2D::Line2D() : a_(0), b_(0), c_(0) {};

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

double Line2D::a() const { return a_; }
double Line2D::b() const { return b_; }
double Line2D::c() const { return c_; }

Point2D* Line2D::interseption(const Line2D& l) const { return findInterseption(l); }
Line2D* Line2D::perpendicular(const Point2D& p) const { return findPerpendicular(p); }

bool Line2D::checkParallelizm(const Line2D& l) const { return checkParallelizmPrivate(l); }

Point2D* Line2D::findInterseption(const Line2D& l) const {
    double al = l.a(), bl = l.b(), cl = l.c();          // { a1*x + b1*y + c1 = 0
    double D = a_*bl -  b_*al;                          // { a2*x + b2*y + c2 = 0

    if (!D) { return nullptr; }                         // D = |a1 b1|
    return new Point2D(                                 //     |a2 b2|  
        (b_*cl - c_*bl)/D,  
        (a_*cl - c_*al)/D                               //     |b1 c1|      |a1 c1|
        );                                              //     |b2 c2|      |a2 c2|
                                                        // x = -------  y = ------- 
}                                                       //        D            D
    
Line2D* Line2D::findPerpendicular(const Point2D& p) const {
    return new Line2D(a_, b_, -(p.x()*a_ + p.y()*b_));
}

bool Line2D::checkParallelizmPrivate(const Line2D& l) const {
    return (                                    // A1   B1   C1
        (a_*l.b()*l.c() == b_*l.a()*l.c())  &&  // -- = -- = --  <=> A1*B2*C2 = B1*A2*C2 = C1*A2*B2
        (b_*l.a()*l.c() == c_*l.a()*l.b())      // A2   B2   C2
    );
}
