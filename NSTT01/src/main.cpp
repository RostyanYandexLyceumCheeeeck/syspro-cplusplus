#include "headers/AVLTree.h"
#include <iostream>


int main() {
    AVLTree<int> tree;
    tree.isEmpty();
    // int* p = new int;

    int arr[] = {8, 10, 12, 6, 16, 9, 11, 7, 5, 4};
    for (int x: arr) {          //            ╔════════ 10 ════════╗
        tree.insert(x);         //       ╔═══ 6 ═══╗    ||   ╔═══ 12 ═══╗
    }                           //    ╔═ 5    | ╔═ 8 ═╗ ||   11   ||   16
                                //    4  |    | 7  |  9 ||        ||

    for (int value : tree) { std::cout << value << ' '; }
    std::cout << std::endl;

    auto it = tree.begin();
    auto end = tree.end();

    for (; it != end; ++it) { std::cout << *it << ' '; }
    std::cout << std::endl;

    return 0;
}
