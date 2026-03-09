#include <gtest/gtest.h>
#include "headers/ScopedPointerDC.h"
#include "headers/ScopedPointerTO.h"
#include "../../NSTT01/src/headers/AVLTree.h"
#include "../../NSTT01/src/AVLTree.cpp"


int arr[] = {8, 10, 12, 6, 16, 9, 11, 7, 5, 4};

class ScopedPtrDCTest : public ::testing::Test {};

TEST_F(ScopedPtrDCTest, DeepCopyCorrectly1) {
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{5, 6, 7, 8};
    std::vector<int> v3{9, 10, 11, 12};
    std::vector<int> v4{101, 102, 103, 104};
    std::vector<int> v5{105, 106, 107, 108};
    std::vector<int> v6{109, 1010, 1011, 1012};

    std::vector<std::vector<int>> vv1{v1, v2, v3};
    std::vector<std::vector<int>> vv2{v4, v5, v6};

    std::vector<std::vector<std::vector<int>>>* vvv = new std::vector<std::vector<std::vector<int>>>{vv1, vv2};

    ScopedPtrDC<std::vector<std::vector<std::vector<int>>>> pointer{vvv};   

    pointer->pop_back();
    EXPECT_TRUE(pointer->size() == 1);
    EXPECT_TRUE(vvv->size() == 2);

    pointer->pop_back();
    EXPECT_TRUE(pointer->size() == 0);
    EXPECT_TRUE(vvv->size() == 2);

    delete vvv;
}

TEST_F(ScopedPtrDCTest, DeepCopyCorrectly2) {
    AVLTree base_tree;
    for (int x: arr) {                  //            ╔════════ 10 ════════╗
        base_tree.insert(x);            //       ╔═══ 6 ═══╗    ||   ╔═══ 12 ═══╗
    }                                   //    ╔═ 5    | ╔═ 8 ═╗ ||   11   ||   16
                                        //    4  |    | 7  |  9 ||        ||
    ScopedPtrDC<AVLTree> pointer = ScopedPtrDC(&base_tree);
    
    for (int x: arr) {
        pointer->remove(x);
        EXPECT_FALSE(pointer->find(x));
        EXPECT_TRUE(base_tree.find(x));
    }
}

class ScopedPtrTOTest : public ::testing::Test {};

TEST_F(ScopedPtrTOTest, TransferOwnershipCorrectly1) {
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<int> v2{5, 6, 7, 8};
    std::vector<int> v3{9, 10, 11, 12};
    std::vector<int> v4{101, 102, 103, 104};
    std::vector<int> v5{105, 106, 107, 108};
    std::vector<int> v6{109, 1010, 1011, 1012};

    std::vector<std::vector<int>> vv1{v1, v2, v3};
    std::vector<std::vector<int>> vv2{v4, v5, v6};

    std::vector<std::vector<std::vector<int>>>* vvv = new std::vector<std::vector<std::vector<int>>>{vv1, vv2};

    ScopedPtrTO<std::vector<std::vector<std::vector<int>>>> pointer(vvv);    

    pointer->pop_back();
    EXPECT_TRUE(pointer->size() == 1);
    EXPECT_TRUE(vvv->size() == 1);

    pointer->pop_back();
    EXPECT_TRUE(pointer->size() == 0);
    EXPECT_TRUE(vvv->size() == 0);
}

TEST_F(ScopedPtrTOTest, TransferOwnershipCorrectly2) {
    AVLTree* base_tree = new AVLTree();
    for (int x: arr) {          //            ╔════════ 10 ════════╗
        base_tree->insert(x);   //       ╔═══ 6 ═══╗    ||   ╔═══ 12 ═══╗
    }                           //    ╔═ 5    | ╔═ 8 ═╗ ||   11   ||   16
                                //    4  |    | 7  |  9 ||        ||
    ScopedPtrTO<AVLTree> pointer(base_tree);
    
    for (int x: arr) {
        pointer->remove(x);
        EXPECT_FALSE(pointer->find(x));
        EXPECT_FALSE(base_tree->find(x));
    }
}

                                    
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
