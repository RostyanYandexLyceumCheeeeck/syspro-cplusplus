#include <iostream>

#include "headers/Point2D.h"
#include "headers/Line2D.h"


int main() {
    Line2D q = Line2D(-1./2, -2./2, -3./2);
    Line2D l = Line2D(1, 2, 3);
   
    std::cout << l.checkParallelizm(q) << std::endl;
    std::cout << l.a() << " " << l.b() << " " << l.c() << std::endl;
    return 0;
}