#include <gtest/gtest.h>

#include "../src/headers/Line2D.h"


class Point2DTest : public ::testing::Test {
protected:
    Point2D p;
};

TEST_F(Point2DTest, CreatedCorrectly) {
    p = Point2D(1.5, 1.7);
    EXPECT_TRUE(this->p.x() == 1.5);
    EXPECT_TRUE(this->p.y() == 1.7);
}


class Line2DTest : public ::testing::Test {
protected:
    Line2D l;
};

TEST_F(Line2DTest, CreatedNumbersCorrectly) {
    l = Line2D(1, 2, 3);
    EXPECT_TRUE(this->l.a() == 1);
    EXPECT_TRUE(this->l.b() == 2);
    EXPECT_TRUE(this->l.c() == 3);
}

TEST_F(Line2DTest, CheckParallelizmTest1) {
    l = Line2D(1, 2, 3);
    Line2D q = Line2D(2, 4, 6);

    EXPECT_TRUE(this->l.checkParallelizm(q)); 
}


TEST_F(Line2DTest, CheckParallelizmTest2) {
    l = Line2D(1, 2, 3);
    Line2D q = Line2D(-1./2, -2./2, -3./2);

    EXPECT_TRUE(this->l.checkParallelizm(q)); 
}

TEST_F(Line2DTest, CheckParallelizmTest3) {
    l = Line2D(1, 2, 3);
    Line2D q = Line2D(3, 2, 1);

    EXPECT_FALSE(this->l.checkParallelizm(q)); 
}

TEST_F(Line2DTest, CreatedPointsCorrectly1) {
    Point2D p1 = Point2D(1, 1), p2 = Point2D(4, 4);
    Line2D q = Line2D(1, -1, 0);                        //   ^ Y
    l = Line2D(p1, p2);                                 //   |
                                                        //   4        * p2
    EXPECT_TRUE(this->l.a() == 3);                      //   |     
    EXPECT_TRUE(this->l.b() == -3);                     //   2        
    EXPECT_TRUE(this->l.c() == 0);                      //   | * p1   
    EXPECT_TRUE(this->l.checkParallelizm(q));           // O +---2----4---> X
}

TEST_F(Line2DTest, CreatedPointsCorrectly2) {
    Point2D p1 = Point2D(1.5, 1), p2 = Point2D(0, 4);
    Line2D q = Line2D(2, 1, -4);                        //   ^ Y
    l = Line2D(p1, p2);                                 //   |
                                                        //   * p2
    EXPECT_TRUE(this->l.a() == 3);                      //   |\        /  
    EXPECT_TRUE(this->l.b() == 1.5);                    //   2 \       /
    EXPECT_TRUE(this->l.c() == -6);                     //   |  * p1
    EXPECT_TRUE(this->l.checkParallelizm(q));           // O +---2----4---> X
}

                            
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
