#ifndef POINT2D_H_
#define POINT2D_H_


class Point2D {
    double x_, y_;
    
public:
    Point2D();
    Point2D(double x, double y);

    double x() const;
    double y() const;
};

#endif // POINT2D_H_