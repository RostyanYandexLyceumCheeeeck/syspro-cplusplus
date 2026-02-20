#include <iostream>

#include "headers/Point2D.h"


Point2D::Point2D() : x_(0), y_(0) {}
Point2D::Point2D(double x, double y) : x_(x), y_(y) {}

double Point2D::x() const { return x_; }
double Point2D::y() const { return y_; }
