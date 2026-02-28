#include "headers/AVLTree.h"
#include <iostream>
#include <string>
#include <algorithm>


void AVLTree::TreeNode::init(const TreeNode& other) {
    val_ = other.val_;
    height_ = other.height_;
    
    left_ = other.left_     ? new AVLTree::TreeNode(*other.left_)   : nullptr; 
    right_ = other.right_   ? new AVLTree::TreeNode(*other.right_)  : nullptr;
    parent_ = other.parent_ ? new AVLTree::TreeNode(*other.parent_) : nullptr;
}

AVLTree::TreeNode::TreeNode(const TreeNode& other) {
    init(other);
}

AVLTree::TreeNode& AVLTree::TreeNode::operator=(const TreeNode& other) {
    if (left_)   { left_->parent_ = nullptr; delete left_; }
    if (right_)  { right_->parent_ = nullptr; delete right_; }
    if (parent_) { 
        parent_->left_ = (parent_->left_ == this) ? nullptr : parent_->left_; 
        parent_->right_ = (parent_->right_ == this) ? nullptr : parent_->right_; 
        delete parent_; 
    }
    
    init(other);
    return *this;
}

AVLTree::TreeNode::~TreeNode() {
    AVLTree::TreeNode* old_parent = parent_;
    if (parent_) { parent_ = nullptr; delete old_parent; } 
    if (left_)   { left_->parent_ = nullptr; delete left_; } 
    if (right_)  { right_->parent_ = nullptr; delete right_; }
}

bool AVLTree::find(int val) {
    return (bool) find(root_, val);
}

int AVLTree::min() {
    TreeNode* node = min(root_);
    return node ? node->val_ : 0; 
}

int AVLTree::max() {
    TreeNode* node = max(root_);
    return node ? node->val_ : 0; 
}

int AVLTree::pred(int val) {
    TreeNode* node = predPrivate(find(root_, val));
    return node ? node->val_ : 0;
}

int AVLTree::succ(int val) {
    TreeNode* node = succPrivate(find(root_, val));
    return node ? node->val_ : 0;
}

void AVLTree::insert(int val) {
    root_ = insert(root_, val);
}

void AVLTree::remove(int val) {
    // root_ = remove(root_, val);
    root_ = removePrivate(val);
}

AVLTree::TreeNode* AVLTree::find(AVLTree::TreeNode* root, int val) {
    if (!root) { return nullptr; }
    
    if (val == root->val_) { return root; }
    if (val < root->val_) { return find(root->left_, val); }
    return find(root->right_, val);
}

AVLTree::TreeNode* AVLTree::min(AVLTree::TreeNode* root) {
    if (!root || !root->left_) { return root; }
    return min(root->left_);
}

AVLTree::TreeNode* AVLTree::max(AVLTree::TreeNode* root) {
    if (!root || !root->right_) { return root; }
    return max(root->right_);
}

AVLTree::TreeNode* AVLTree::predPrivate(AVLTree::TreeNode* node) {
    if (!node) { return nullptr; }
    
    AVLTree::TreeNode* par_min = node;
    AVLTree::TreeNode* left_max = max(node->left_);
    while (par_min->parent_ && par_min->parent_->val_ >= node->val_) {
        par_min = par_min->parent_;
    }
    
    if (left_max) {
        if (par_min->parent_ && left_max->val_ < par_min->parent_->val_) {
            return par_min->parent_;
        }
        if (left_max->val_ < node->val_) { return left_max; }
        return nullptr;
    }
    return par_min->parent_;
}

AVLTree::TreeNode* AVLTree::succPrivate(AVLTree::TreeNode* node) {
    if (!node) { return nullptr; }
    
    AVLTree::TreeNode* par_max = node;
    AVLTree::TreeNode* right_min = min(node->right_);
    while (par_max->parent_ && par_max->parent_->val_ <= node->val_) {
        par_max = par_max->parent_;
    }
    
    if (right_min) {
        if (par_max->parent_ && right_min->val_ > par_max->parent_->val_) {
            return par_max->parent_;
        }
        if (right_min->val_ > node->val_) { return right_min; }
        return nullptr;
    }
    return par_max->parent_;
}

AVLTree::TreeNode* AVLTree::insert(AVLTree::TreeNode* root, int val) {
    if (!root) { return new TreeNode(val); }

    if (val < root->val_) {
        linked2Node(root, insert(root->left_, val), true);
    } else {
        linked2Node(root, insert(root->right_, val), false);
    }
    return rotationExecutor(root);
}

AVLTree::TreeNode* AVLTree::removePrivate(int val) {
    TreeNode* target = find(root_, val);
    if (!target) { return root_; }

    AVLTree::TreeNode* baby = target;
    if (target->left_ && target->right_) { 
        baby = min(target->right_); 
        linked2Node(baby->parent_, baby->right_, (baby != target->right_)); 
    } else if (target->right_) { 
        baby = target->right_; 
    } else if (target->left_) { 
        baby = target->left_; 
    } 
    // baby = t OR min(t.r) OR t.r OR t.l

    target->val_ = baby->val_;
    AVLTree::TreeNode* par_baby = baby->parent_;
    if (par_baby) { linked2Node(par_baby, nullptr, (par_baby->left_ == baby)); }

    baby->left_ = nullptr;
    baby->right_ = nullptr;
    baby->parent_ = nullptr;
    delete baby;
    return bubbleRotationExecutor(par_baby);
}

AVLTree::TreeNode* AVLTree::bubbleRotationExecutor(AVLTree::TreeNode* root) {
    if (!root) { return nullptr; }

    AVLTree::TreeNode* upd_root = rotationExecutor(root);
    return upd_root->parent_ ? bubbleRotationExecutor(upd_root->parent_) : upd_root;
}

AVLTree::TreeNode* AVLTree::rotationExecutor(AVLTree::TreeNode* root) {
    if (!root) { return nullptr; }

    int balance = getBalance(root);
    if (balance == 2) {
        root = ((getBalance(root->right_) == -1) ? 
                bigLeftRotation(root) : 
                miniLeftRotation(root));
    } else if (balance == -2) {
        root = ((getBalance(root->left_) == +1) ? 
                bigRightRotation(root) : 
                miniRightRotation(root));
    }

    root->height_ = getHeight(root);
    return root;
}

AVLTree::TreeNode* AVLTree::bigLeftRotation(AVLTree::TreeNode* root) {
    // linked2Node(root, miniRightRotation(root->right_), false);
    miniRightRotation(root->right_);
    return miniLeftRotation(root);
}

AVLTree::TreeNode* AVLTree::bigRightRotation(AVLTree::TreeNode* root) {
    // linked2Node(root, miniLeftRotation(root->left_), true);
    miniLeftRotation(root->left_);
    return miniRightRotation(root);
}

AVLTree::TreeNode* AVLTree::miniLeftRotation(AVLTree::TreeNode* root) {
    root->height_--;
    root->right_->height_++;
    
    // save pointers
    AVLTree::TreeNode* old_par = root->parent_;
    AVLTree::TreeNode* upd_root = root->right_;
    bool leftward = (old_par && old_par->left_ == root);
    
    upd_root->parent_ = old_par;
    linked2Node(root, upd_root->left_, false);
    linked2Node(upd_root, root, true);
    linked2Node(old_par, upd_root, leftward);
    
    return upd_root;
}

AVLTree::TreeNode* AVLTree::miniRightRotation(AVLTree::TreeNode* root) {
    root->height_--;
    root->left_->height_++;

    // save pointers
    AVLTree::TreeNode* old_par = root->parent_;
    AVLTree::TreeNode* upd_root = root->left_;
    bool leftward = (old_par && old_par->left_ == root);

    upd_root->parent_ = old_par;
    linked2Node(root, upd_root->right_, true);
    linked2Node(upd_root, root, false);
    linked2Node(old_par, upd_root, leftward);

    return upd_root;
}

int AVLTree::getHeight(AVLTree::TreeNode* root) {
    if (!root) { return 0; }
    int lh = ((!root->left_)  ? 0 : root->left_->height_);     // height left
    int rh = ((!root->right_) ? 0 : root->right_->height_);    // height right
    return (lh > rh ? lh : rh) + 1;
}

int AVLTree::getBalance(AVLTree::TreeNode* root) {
    if (!root) { return 0; }
    return getHeight(root->right_) - getHeight(root->left_);
}

void AVLTree::linked2Node(AVLTree::TreeNode* father, AVLTree::TreeNode* baby, bool leftward) {
    if (!father) { return; }

    if (leftward) {
        father->left_ = baby;
    } else {
        father->right_ = baby;
    }
    
    if (baby) { baby->parent_ = father; } 
}

void AVLTree::printTree(AVLTree::TreeNode* root, unsigned int counter) {
    if (!root) { return; }
    std::string st(counter, '|');
    std::cout << st << ' ' << root->val_ << " {" << std::endl;
    std::cout << st << "left: " << std::endl;
    printTree(root->left_, counter+1);
    std::cout << st << "right: " << std::endl;
    printTree(root->right_, counter+1);
    std::cout << st << ' ' << " }" << std::endl;
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

AVLTree::AVLTree(const AVLTree& other) {
    root_ = new AVLTree::TreeNode(*other.root_);
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    delete root_;
    root_ = new AVLTree::TreeNode(*other.root_);
    return *this;
}

AVLTree::~AVLTree() {
    if (!root_) { return; }
    delete root_;
}
