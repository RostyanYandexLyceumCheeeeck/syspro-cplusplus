#ifndef LINE2D_H_
#define LINE2D_H_

#include "Point2D.h"
#include <optional>

const double EPS = 1e-9;

class Line2D {
    double a_, b_, c_;
 
    Line2D(double a, double b, double c);
    Line2D(const Point2D& p1, const Point2D& p2);


public:
    static std::optional<Line2D> createLine(double a, double b, double c);
    static std::optional<Line2D> createLine(const Point2D& p1, const Point2D& p2);

    double a() const;
    double b() const;
    double c() const;

    std::optional<Point2D> intersection(const Line2D& l) const;
    std::optional<Line2D> perpendicular(const Point2D& p) const;

    bool checkParallelizm(const Line2D& l) const;
    bool checkCoincidence(const Line2D& l) const;
};

#endif // LINE2D_H_