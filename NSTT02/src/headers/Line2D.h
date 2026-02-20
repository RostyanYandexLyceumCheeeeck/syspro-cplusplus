#ifndef LINE2D_H_
#define LINE2D_H_

#include "Point2D.h"


class Line2D {
    double a_, b_, c_;

public:
    Line2D();
    Line2D(double a, double b, double c);
    Line2D(const Point2D& p1, const Point2D& p2);

    Point2D* interseption(const Line2D& l) const;
    Line2D* perpendicular(const Point2D& p) const;

    double a() const;
    double b() const;
    double c() const;

    bool checkParallelizm(const Line2D& l) const;

private:
    Point2D* findInterseption(const Line2D& l) const;
    Line2D* findPerpendicular(const Point2D& p) const;
    bool checkParallelizmPrivate(const Line2D& l) const; 
};

#endif // LINE2D_H_