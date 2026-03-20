#include <string>
#include <gtest/gtest.h>
#include "headers/Matrix2D.h"


template<typename T>
Matrix2D<T> fill(const std::vector<T>& arr, size_t n, size_t m) {
    EXPECT_EQ(n * m, arr.size());

    Matrix2D<T> res(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            res[i][j] = arr[i*m + j];
        }
    }
    return res;
}


class DoubleMatrix2DTest : public ::testing::Test {
protected:
    Matrix2D<double> mat;
};

TEST_F(DoubleMatrix2DTest, InitVectorCorrectly) {
    std::vector<double> v = {0.0, 1.0, 7.2};
    mat = Matrix2D<double>(v);
    
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            EXPECT_EQ((i == j ? v[i] : 0.0), mat[i][j]);
        }
    }
}

TEST_F(DoubleMatrix2DTest, InitArrayCorrectly) {
    std::vector<double> v = {0.0, 1.0, 7.2};
    size_t size = v.size();
    double* arr = v.data();

    mat = Matrix2D<double>(arr, size);

    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            EXPECT_EQ((i == j ? v[i] : 0.0), mat[i][j]);
        }
    }
}

TEST_F(DoubleMatrix2DTest, EqualCorrectly) {
    std::vector<double> v = {0.0, 1.0, 7.2};
    mat = Matrix2D<double>(v);
    Matrix2D<double> other = Matrix2D<double>(v);

    EXPECT_TRUE(mat == other);
    EXPECT_FALSE(mat != other);
}

TEST_F(DoubleMatrix2DTest, NotEqualCorrectly) {
    std::vector<double> v = {0.0, 1.0, 7.2};
    mat = Matrix2D<double>(v);
    Matrix2D<double> other = Matrix2D<double>(3, 3);

    EXPECT_TRUE(mat != other);
    EXPECT_FALSE(mat == other);
}

TEST_F(DoubleMatrix2DTest, AdditionMatrixCorrectly1) {
    std::vector<double> v = {0.0, 
                                  1.0, 
                                       7.2
                            };
           // +  //     
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
           // || //     
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };

    mat = Matrix2D<double>(v);
    Matrix2D<double> other = fill<double>(z, 3, 3);
    Matrix2D<double> answer = mat + other;
    Matrix2D<double> expected = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(answer == expected);
}

TEST_F(DoubleMatrix2DTest, AdditionMatrixCorrectly2) {
    std::vector<double> v = {0.0, 
                                  1.0, 
                                       7.2
                            };
           // += //     
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
           // || //     
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };

    mat = Matrix2D<double>(v);
    Matrix2D<double> other = fill<double>(z, 3, 3);
    mat += other;
    Matrix2D<double> expected = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(mat == expected);
}

TEST_F(DoubleMatrix2DTest, AdditionScalarCorrectly1) {
    std::vector<double> v = {0.0, 0.0, 0.0, 
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 7.2
                            };
           
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
                
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };
    
    double c1 = 0., c2 = -3.3, c3 = 3.3;

    mat = fill<double>(v, 3, 3) + c1;
    Matrix2D<double> mat2 = fill<double>(z, 3, 3) + c2;
    Matrix2D<double> mat3 = fill<double>(x, 3, 3) + c3;
    
    for (double& i : v) { i += c1; }
    for (double& i : z) { i += c2; }
    for (double& i : x) { i += c3; }
    
    Matrix2D<double> expected1 = fill<double>(v, 3, 3);
    Matrix2D<double> expected2 = fill<double>(z, 3, 3);
    Matrix2D<double> expected3 = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(mat == expected1);
    EXPECT_TRUE(mat2 == expected2);
    EXPECT_TRUE(mat3 == expected3);
}

TEST_F(DoubleMatrix2DTest, AdditionScalarCorrectly2) {
    std::vector<double> v = {0.0, 0.0, 0.0, 
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 7.2
                            };
           
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
                
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };
    
    double c1 = 0., c2 = -3.3, c3 = 3.3;

    mat = fill<double>(v, 3, 3);
    Matrix2D<double> mat2 = fill<double>(z, 3, 3);
    Matrix2D<double> mat3 = fill<double>(x, 3, 3);
    
    mat += c1;
    mat2 += c2;
    mat3 += c3;

    for (double& i : v) { i += c1; }
    for (double& i : z) { i += c2; }
    for (double& i : x) { i += c3; }
    
    Matrix2D<double> expected1 = fill<double>(v, 3, 3);
    Matrix2D<double> expected2 = fill<double>(z, 3, 3);
    Matrix2D<double> expected3 = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(mat == expected1);
    EXPECT_TRUE(mat2 == expected2);
    EXPECT_TRUE(mat3 == expected3);
}

TEST_F(DoubleMatrix2DTest, MultiplicationMatrixCorrectly1) {
    std::vector<double> v = {0.0, 0.0, 0.0, 
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 7.2
                            };
           
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
                
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };
    

    Matrix2D<double> mat1 = fill<double>(v, 3, 3);
    Matrix2D<double> mat2 = fill<double>(z, 3, 3);
    Matrix2D<double> mat3 = fill<double>(x, 3, 3);
    
    Matrix2D<double> ans1 = mat1 * mat2;
    Matrix2D<double> ans2 = mat2 * mat3;
    Matrix2D<double> ans3 = mat3 * mat1;
    
    v = { 0.0 ,  0.0,  0.0 , 
          4.5 ,  5.2,  6.6 ,
         52.56, 57.6, 71.28
        }; // v*z
           
    z = { 31.9 , 38.4 ,  67.5 , 
          76.08, 94.04, 160.68, 
         115.57, 143.4, 243.99
        }; // z*x
                
    x = {0.0, 2.0,  21.6 , 
         0.0, 6.2,  47.52, 
         0.0, 8.0, 123.12
        }; // x*v

    Matrix2D<double> expected1 = fill<double>(v, 3, 3);
    Matrix2D<double> expected2 = fill<double>(z, 3, 3);
    Matrix2D<double> expected3 = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(ans1 == expected1);
    EXPECT_TRUE(ans2 == expected2);
    EXPECT_TRUE(ans3 == expected3);
}

TEST_F(DoubleMatrix2DTest, MultiplicationMatrixCorrectly2) {
    std::vector<double> v = {0.0, 0.0, 0.0, 
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 7.2
                            };
           
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
                
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };
    

    Matrix2D<double> mat1 = fill<double>(v, 3, 3);
    Matrix2D<double> mat2 = fill<double>(z, 3, 3);
    Matrix2D<double> mat3 = fill<double>(x, 3, 3);
    
    Matrix2D<double> ans1 = mat1;
    Matrix2D<double> ans2 = mat2;
    Matrix2D<double> ans3 = mat3;

    ans1 *= mat2;
    ans2 *= mat3;
    ans3 *= mat1;
    
    v = { 0.0 ,  0.0,  0.0 , 
          4.5 ,  5.2,  6.6 ,
         52.56, 57.6, 71.28
        }; // v*z
           
    z = { 31.9 , 38.4 ,  67.5 , 
          76.08, 94.04, 160.68, 
         115.57, 143.4, 243.99
        }; // z*x
                
    x = {0.0, 2.0,  21.6 , 
         0.0, 6.2,  47.52, 
         0.0, 8.0, 123.12
        }; // x*v

    Matrix2D<double> expected1 = fill<double>(v, 3, 3);
    Matrix2D<double> expected2 = fill<double>(z, 3, 3);
    Matrix2D<double> expected3 = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(ans1 == expected1);
    EXPECT_TRUE(ans2 == expected2);
    EXPECT_TRUE(ans3 == expected3);
}

TEST_F(DoubleMatrix2DTest, MultiplicationScalarCorrectly1) {
    std::vector<double> v = {0.0, 0.0, 0.0, 
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 7.2
                            };
           
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
                
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };
    
    double c1 = 0., c2 = 7.7, c3 = (-1./3);
    
    Matrix2D<double> ans1 = fill<double>(v, 3, 3) * c1;
    Matrix2D<double> ans2 = fill<double>(z, 3, 3) * c2;
    Matrix2D<double> ans3 = fill<double>(x, 3, 3) * c3;
    
    for (double& i : v) { i *= c1; }
    for (double& i : z) { i *= c2; }
    for (double& i : x) { i *= c3; }

    Matrix2D<double> expected1 = fill<double>(v, 3, 3);
    Matrix2D<double> expected2 = fill<double>(z, 3, 3);
    Matrix2D<double> expected3 = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(ans1 == expected1);
    EXPECT_TRUE(ans2 == expected2);
    EXPECT_TRUE(ans3 == expected3);
}

TEST_F(DoubleMatrix2DTest, MultiplicationScalarCorrectly2) {
    std::vector<double> v = {0.0, 0.0, 0.0, 
                             0.0, 1.0, 0.0,
                             0.0, 0.0, 7.2
                            };
           
    std::vector<double> z = {1. , 2. , 3., 
                             4.5, 5.2, 6.6, 
                             7.3, 8. , 9.9
                            };
                
    std::vector<double> x = {1. , 2. , 3., 
                             4.5, 6.2, 6.6, 
                             7.3, 8. , 17.1
                            };
    
    double c1 = 0., c2 = 7.7, c3 = (-1./3);
    
    Matrix2D<double> ans1 = fill<double>(v, 3, 3);
    Matrix2D<double> ans2 = fill<double>(z, 3, 3);
    Matrix2D<double> ans3 = fill<double>(x, 3, 3);
    
    ans1 *= c1;
    ans2 *= c2;
    ans3 *= c3;
    
    for (double& i : v) { i *= c1; }
    for (double& i : z) { i *= c2; }
    for (double& i : x) { i *= c3; }

    Matrix2D<double> expected1 = fill<double>(v, 3, 3);
    Matrix2D<double> expected2 = fill<double>(z, 3, 3);
    Matrix2D<double> expected3 = fill<double>(x, 3, 3);
    
    EXPECT_TRUE(ans1 == expected1);
    EXPECT_TRUE(ans2 == expected2);
    EXPECT_TRUE(ans3 == expected3);
}

                            
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
