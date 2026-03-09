#include <iostream>

#include "headers/Point2D.h"
#include "headers/Line2D.h"


int main() {
    std::optional<Line2D> q = Line2D::createLine(-1/2, -2/2, -3/2);
    std::optional<Line2D> l = Line2D::createLine(1, 2, 3);
    if (l && q) {
        std::cout << l->checkParallelizm(q.value()) << std::endl;
        std::cout << l->a() << " " << l->b() << " " << l->c() << std::endl;
    }
    return 0;
}