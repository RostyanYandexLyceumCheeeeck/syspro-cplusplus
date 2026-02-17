#include "headers/AVLTree.h"
#include <iostream>
#include <string>
#include <algorithm>


AVLTree::AVLTree() {
    root_ = nullptr;
}
 
AVLTree::AVLTree(AVLTree::TreeNode* root) {
    root_ = root;
}

AVLTree::TreeNode* AVLTree::find(int val) {
    return find(root_, val); 
}

AVLTree::TreeNode* AVLTree::min() {
    return min(root_);
}

AVLTree::TreeNode* AVLTree::max() {
    return max(root_);
}

AVLTree::TreeNode* AVLTree::pred(AVLTree::TreeNode* node) {
    return predPrivate(node);
}

AVLTree::TreeNode* AVLTree::succ(AVLTree::TreeNode* node) {
    return succPrivate(node);
}

void AVLTree::insert(int val) {
    root_ = insert(root_, val);
}

void AVLTree::remove(int val) {
    root_ = remove(root_, val);
}

AVLTree::TreeNode* AVLTree::find(AVLTree::TreeNode* root, int val) {
    if (!root) { return nullptr; }
    
    if (val == root->val) { return root; }
    if (val < root->val) { return find(root->left, val); }
    return find(root->right, val);
}

AVLTree::TreeNode* AVLTree::min(AVLTree::TreeNode* root) {
    if (!root || !root->left) { return root; }
    return min(root->left);
}

AVLTree::TreeNode* AVLTree::max(AVLTree::TreeNode* root) {
    if (!root || !root->right) { return root; }
    return max(root->right);
}

AVLTree::TreeNode* AVLTree::predPrivate(AVLTree::TreeNode* node) {
    if (!node) { return nullptr; }
    
    AVLTree::TreeNode* par_min = node;
    AVLTree::TreeNode* left_max = max(node->left);
    while (par_min->parent && par_min->parent->val >= par_min->val) {
        par_min = par_min->parent;
    }
    
    if (left_max) {
        if (par_min->parent && left_max->val < par_min->parent->val) {
            return par_min->parent;
        }
        if (left_max->val < node->val) { return left_max; }
        return nullptr;
    }
    return par_min->parent;
}

AVLTree::TreeNode* AVLTree::succPrivate(AVLTree::TreeNode* node) {
    if (!node) { return nullptr; }
    
    AVLTree::TreeNode* par_max = node;
    AVLTree::TreeNode* right_min = max(node->left);
    while (par_max->parent && par_max->parent->val <= par_max->val) {
        par_max = par_max->parent;
    }
    
    if (right_min) {
        if (par_max->parent && right_min->val > par_max->parent->val) {
            return par_max->parent;
        }
        if (right_min->val > node->val) { return right_min; }
        return nullptr;
    }
    return par_max->parent;
}

AVLTree::TreeNode* AVLTree::insert(AVLTree::TreeNode* root, int val) {
    if (!root) { return new AVLTree::TreeNode(val); }

    if (val < root->val) {
        linked2Node(root, insert(root->left, val), true);
        // root->left = insert(root->right, val);
        // root->left->parent = root;
    } else {
        linked2Node(root, insert(root->right, val), false);
        // root->right = insert(root->right, val);
        // root->right->parent = root;
    }
    return rotationExecutor(root);
}

AVLTree::TreeNode* AVLTree::remove(AVLTree::TreeNode* root, int val) {
    if (!root) { return nullptr; }

    if (val == root->val) {
        AVLTree::TreeNode* baby = nullptr;
        if (root->left && root->right) {
            baby = min(root->right);

            // root->left->parent = baby;
            // root->right->parent = baby;
            // linkGrandfatherGrandson(baby, baby->right);
            // baby->left = root->left;
            // baby->right = root->right;

            linked2Node(baby->parent, baby->right, true);
            bubbleRotationExecutor(baby->parent);
            linked2Node(baby, root->left, true);
            linked2Node(baby, root->right, false);

        } else if (root->left) {
            baby = root->left;
        } else if (root->right) {
            baby = root->right;
        }

        delete root;
        return rotationExecutor(baby); 
    }

    if (val < root->val) {
        linked2Node(root, remove(root->left, val), true); 
    } else {
        linked2Node(root, remove(root->right, val), false); 
    }
    return rotationExecutor(root); 
}

AVLTree::TreeNode* AVLTree::bubbleRotationExecutor(AVLTree::TreeNode* root) {
    if (!root) { return nullptr; }

    AVLTree::TreeNode* upd_root = rotationExecutor(root);
    if (root->parent) { 
        linked2Node(root->parent, upd_root, (root->parent->left == root)); 
        return bubbleRotationExecutor(upd_root->parent);
    }
    return upd_root;
}

AVLTree::TreeNode* AVLTree::rotationExecutor(AVLTree::TreeNode* root) {
    if (!root) { return nullptr; }

    int balance = getBalance(root);
    if (balance == 2) {
        root = ((getBalance(root->right) == -1) ? 
                bigLeftRotation(root) : 
                miniLeftRotation(root));
    } else if (balance == -2) {
        root = ((getBalance(root->left) == +1) ? 
                bigRightRotation(root) : 
                miniRightRotation(root));
    }

    root->height = getHeight(root);
    return root;
}

AVLTree::TreeNode* AVLTree::bigLeftRotation(AVLTree::TreeNode* root) {
    // root->right = miniRightRotation(root->right);
    linked2Node(root, miniRightRotation(root->right), false);
    return miniLeftRotation(root);
}

AVLTree::TreeNode* AVLTree::bigRightRotation(AVLTree::TreeNode* root) {
    // root->left = miniLeftRotation(root->left);
    linked2Node(root, miniLeftRotation(root->left), true);
    return miniRightRotation(root);
}

AVLTree::TreeNode* AVLTree::miniLeftRotation(AVLTree::TreeNode* root) {
    root->height--;
    root->right->height++;

    AVLTree::TreeNode* upd_root = root->right;
    // root->right = root->right->left;
    // upd_root->left = root;
    upd_root->parent = root->parent;
    linked2Node(root, upd_root->left, false);
    linked2Node(upd_root, root, true);

    return upd_root;
}

AVLTree::TreeNode* AVLTree::miniRightRotation(AVLTree::TreeNode* root) {
    root->height--;
    root->left->height++;

    AVLTree::TreeNode* upd_root = root->left;
    // root->left = root->left->right;
    // upd_root->right = root;
    upd_root->parent = root->parent;
    linked2Node(root, upd_root->right, true);
    linked2Node(upd_root, root, false);

    return upd_root;
}

int AVLTree::getHeight(AVLTree::TreeNode* root) {
    if (!root) { return 0; }
    int lh = ((!root->left)  ? 0 : root->left->height);     // height left
    int rh = ((!root->right) ? 0 : root->right->height);    // height right
    return (lh > rh ? lh : rh) + 1;
}

int AVLTree::getBalance(AVLTree::TreeNode* root) {
    if (!root) { return 0; }
    return getHeight(root->right) - getHeight(root->left);
}

void AVLTree::linked2Node(AVLTree::TreeNode* father, AVLTree::TreeNode* baby, bool leftward) {
    if (!father) { return; }

    if (leftward) {
        father->left = baby;
    } else {
        father->right = baby;
    }
    
    if (baby) { baby->parent = father; } 
}

void AVLTree::printTree(AVLTree::TreeNode* root, unsigned int counter) {
    if (!root) { return; }
    std::string st(counter, '|');
    std::cout << st << ' ' << root->val << " {" << std::endl;
    std::cout << st << "left: " << std::endl;
    printTree(root->left, counter+1);
    std::cout << st << "right: " << std::endl;
    printTree(root->right, counter+1);
    std::cout << st << ' ' << " }" << std::endl;
}

void AVLTree::rmTree(AVLTree::TreeNode* root) {
        if (!root) { return; }
        rmTree(root->left);
        rmTree(root->right);
        delete root;
    }

bool AVLTree::isEmpty() {
    return (!root_);
} 

int AVLTree::getHeight() {
    return getHeight(root_);
}

void AVLTree::printTree() {
    printTree(root_, 0);
    std::cout << std::endl;
}

AVLTree::~AVLTree() {
    rmTree(root_);
}
