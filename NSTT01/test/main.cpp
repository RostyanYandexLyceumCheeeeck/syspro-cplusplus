#include <gtest/gtest.h>
#include "headers/AVLTree.h"

class AVLTreeTest : public ::testing::Test {
protected:
    AVLTree tree;

};

TEST_F(AVLTreeTest, IsEmpty) {
    EXPECT_TRUE(this->tree.isEmpty());
}

TEST_F(AVLTreeTest, InsertsElementsCorrectly) {
    this->tree.insert(7);
    EXPECT_FALSE(this->tree.isEmpty());
    EXPECT_TRUE(this->tree.find(7));
}


TEST_F(AVLTreeTest, RemovesElementsCorrectly) {
    for (int i = 0; i < 10; i++) {
        this->tree.insert(i);
    }

    for (int i = 0; i < 10; i++) {
        this->tree.remove(i);
        EXPECT_FALSE(this->tree.find(i));
    }

    EXPECT_TRUE(this->tree.isEmpty());
}


TEST_F(AVLTreeTest, GetsMinimumCorrectly) {
    this->tree.insert(7);
    this->tree.insert(3);
    this->tree.insert(9);
    this->tree.insert(14);
    this->tree.insert(2);

    EXPECT_EQ(this->tree.min()->val, 2);
    this->tree.remove(2);

    EXPECT_EQ(this->tree.min()->val, 3);
    this->tree.remove(3);

    EXPECT_EQ(this->tree.min()->val, 7);
    this->tree.remove(7);
    EXPECT_EQ(this->tree.min()->val, 9);
}


TEST_F(AVLTreeTest, GetsMaximumCorrectly) {
    this->tree.insert(7);
    this->tree.insert(3);
    this->tree.insert(9);
    this->tree.insert(14);
    this->tree.insert(2);

    EXPECT_EQ(this->tree.max()->val, 14);
    this->tree.remove(14);

    EXPECT_EQ(this->tree.max()->val, 9);
    this->tree.remove(9);

    EXPECT_EQ(this->tree.max()->val, 7);
    this->tree.remove(7);
    EXPECT_EQ(this->tree.max()->val, 3);
}

TEST_F(AVLTreeTest, GetsPredCorrectly) {
    this->tree.insert(7);
    this->tree.insert(3);
    this->tree.insert(9);
    this->tree.insert(14);
    this->tree.insert(2);

    EXPECT_EQ(this->tree.pred(this->tree.find(14)), this->tree.find(9));
    EXPECT_EQ(this->tree.pred(this->tree.find(9)), this->tree.find(7));
    EXPECT_EQ(this->tree.pred(this->tree.find(7)), this->tree.find(3));
    EXPECT_EQ(this->tree.pred(this->tree.find(3)), this->tree.find(2));
    EXPECT_EQ(this->tree.pred(this->tree.find(2)), nullptr);
}

TEST_F(AVLTreeTest, RotationsCorrectly) {
                            //         ╔═════ 10 ═════╗
    this->tree.insert(8);         //    ╔═══ 8 ═══╗ | ╔═══ 12 ═══╗ 
    this->tree.insert(10);        //    6 ═╗ |    9 | 11    |   16
    this->tree.insert(12);        //    |  7 |      |       |
    this->tree.insert(6);         //               
    this->tree.insert(16);        //           ╔═════ 10 ═════╗
    this->tree.insert(9);         //      ╔═══ 8 ═══╗ || ╔═══ 12 ═══╗
    this->tree.insert(11);        //    ╔═ 6 ═╗ |   9 || 11    |   16
    this->tree.insert(7);         //    5  |  7 |     ||       |
                            //
    this->tree.insert(5);         //                   ╔═══════ 10 ═══════╗
    this->tree.insert(4);         //            ╔═════ 8 ═════╗ || ╔═════ 12 ═════╗
                            //       ╔═══ 6 ═══╗ |      9 || 11     ||     16
                            //    ╔═ 5    |    7 |        ||        ||
                            //    4  |    |      |        ||        ||
    EXPECT_EQ(this->tree.getHeight(), 4);
}                           //            ╔════════ 10 ════════╗
                            //       ╔═══ 6 ═══╗    ||   ╔═══ 12 ═══╗
                            //    ╔═ 5    | ╔═ 8 ═╗ ||   11   ||   16
                            //    4  |    | 7  |  9 ||        ||

                            
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
