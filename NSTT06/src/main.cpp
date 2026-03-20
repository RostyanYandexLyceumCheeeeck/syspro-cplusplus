#include <iostream>
#include "headers/Matrix2D.h"


void test0() {
    Matrix2D<int> mat(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            mat[i][j] = (int) (3*i + j);
        }
    }
    std::cout << mat;
}


int main() {
    test0();

    return 0;
}