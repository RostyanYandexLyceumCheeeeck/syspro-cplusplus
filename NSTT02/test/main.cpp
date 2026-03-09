#include <gtest/gtest.h>

#include "headers/Line2D.h"
#include "headers/Point2D.h"

class Point2DTest : public ::testing::Test {
protected:
    Point2D p;
};

TEST_F(Point2DTest, CreatedCorrectly) {
    p = Point2D(1.5, 1.7);
    EXPECT_DOUBLE_EQ(this->p.x(), 1.5);
    EXPECT_DOUBLE_EQ(this->p.y(), 1.7);
}


class Line2DTest : public ::testing::Test {
protected:
    std::optional<Line2D> l;
    std::optional<Line2D> q;
};

TEST_F(Line2DTest, CreatedNumbersCorrectly) {
    this->l = Line2D::createLine(1, 2, 3);
    ASSERT_TRUE(l);
    EXPECT_LT((this->l->a() - 1), EPS);
    EXPECT_LT((this->l->b() - 2), EPS);
    EXPECT_LT((this->l->c() - 3), EPS);
}

TEST_F(Line2DTest, CheckParallelizmTest1) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(2, 4, 6);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_TRUE(this->l->checkParallelizm(this->q.value())); 
}


TEST_F(Line2DTest, CheckParallelizmTest2) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(-1./2, -2./2, -3./2);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_TRUE(this->l->checkParallelizm(this->q.value())); 
}

TEST_F(Line2DTest, CheckParallelizmTest3) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(3, 2, 1);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_FALSE(this->l->checkParallelizm(this->q.value())); 
}

TEST_F(Line2DTest, CheckParallelizmTest4) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(2, 4, 7);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_TRUE(this->l->checkParallelizm(this->q.value())); 
}

TEST_F(Line2DTest, CheckCoincidenceTest1) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(2, 4, 6);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_TRUE(this->l->checkCoincidence(this->q.value())); 
}


TEST_F(Line2DTest, CheckCoincidenceTest2) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(-1./2, -2./2, -3./2);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_TRUE(this->l->checkCoincidence(this->q.value())); 
}

TEST_F(Line2DTest, CheckCoincidenceTest3) {
    this->l = Line2D::createLine(1, 2, 3);
    this->q = Line2D::createLine(2, 4, 7);

    ASSERT_TRUE(this->l);
    ASSERT_TRUE(this->q);
    EXPECT_FALSE(this->l->checkCoincidence(this->q.value())); 
}

TEST_F(Line2DTest, CreatedPointsCorrectly1) {
    Point2D p1 = Point2D(1, 1), p2 = Point2D(4, 4);
    this->q = Line2D::createLine(1, -1, 0);                     //   ^ Y
    this->l = Line2D::createLine(p1, p2);                       //   |
                                                                //   4        * p2
    EXPECT_LT((this->l->a() - 3), EPS);                         //   |     
    EXPECT_LT((this->l->b() - -3), EPS);                        //   2        
    EXPECT_LT((this->l->c() - 0), EPS);                         //   | * p1   
    EXPECT_TRUE(this->l->checkParallelizm(this->q.value()));    // O +---2----4---> X
}

TEST_F(Line2DTest, CreatedPointsCorrectly2) {
    Point2D p1 = Point2D(1.5, 1), p2 = Point2D(0, 4);
    this->q = Line2D::createLine(2, 1, -4);                     //   ^ Y
    this->l = Line2D::createLine(p1, p2);                       //   |
                                                                //   * p2
    EXPECT_LT((this->l->a() - 3), EPS);                         //   |\                 //
    EXPECT_LT((this->l->b() - 1.5), EPS);                       //   2 \                //
    EXPECT_LT((this->l->c() - (-6)), EPS);                      //   |  * p1
    EXPECT_TRUE(this->l->checkParallelizm(this->q.value()));    // O +---2----4---> X
}

                            
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
