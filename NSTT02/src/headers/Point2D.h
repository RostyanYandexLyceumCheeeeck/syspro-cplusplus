#ifndef POINT2D_H_
#define POINT2D_H_


class Point2D {
    double x_, y_;
    
public:
    Point2D(double x = 0, double y = 0) : x_(x), y_(y) {}

    double x() const { return x_; }
    double y() const { return y_; }
};

#endif // POINT2D_H_