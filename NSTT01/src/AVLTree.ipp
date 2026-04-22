#pragma once
#include "headers/AVLTree.h"

// =============== TreeNode ctor`s and optor`s  =============== 
template <typename T>
AVLTree<T>::TreeNode::TreeNode(AVLTree<T>::TreeNode&& other) {  
    if (this != &other) {
        val_ = other.val_;
        height_ = other.height_; 
        std::swap(left_, other.left_); 
        std::swap(right_, other.right_); 
        std::swap(parent_, other.parent_); 
    }
}

template <typename T>
AVLTree<T>::TreeNode& AVLTree<T>::TreeNode::operator=(TreeNode&& other) {
    if (this != &other) { 
        val_ = other.val_;
        height_ = other.height_; 
        std::swap(left_, other.left_); 
        std::swap(right_, other.right_); 
        std::swap(parent_, other.parent_); 
    }
    return *this;
}
// =^^^^^^^^^^^^^= TreeNode ctor`s and optor`s =^^^^^^^^^^^^^= 

// =============== Iterator optor`s  =============== 
template <typename T>
AVLTree<T>::Iterator& AVLTree<T>::Iterator::operator++() {
            if (!currentNode_) return *this;

            if (currentNode_->right_) {
                currentNode_ = currentNode_->right_;
                while (currentNode_->left_) {currentNode_ = currentNode_->left_;}   
            } else {
                TreeNode* parent = currentNode_->parent_;
                while (parent && currentNode_ == parent->right_) {
                    currentNode_ = parent;
                    parent = parent->parent_;
                }
                currentNode_ = parent;
            }
            return *this;
        }

template <typename T>
AVLTree<T>::Iterator& AVLTree<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}
// =^^^^^^^^^^^^^= Iterator optor`s =^^^^^^^^^^^^^= 

// =============== AVLTree<T> ctor`s and optor`s  =============== 
template <typename T>
AVLTree<T>::AVLTree(AVLTree<T>&& other) {
    if (this != &other) { std::swap(root_, other.root_); }
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& other) {
    root_ = other.root_ ? recursiveCopied(nullptr, *other.root_) : nullptr;
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree<T>&& other) {
    if (this != &other) { std::swap(root_, other.root_); }
    return *this;
}

template <typename T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other) {
    recursiveDelete(root_);
    root_ = other.root_ ? recursiveCopied(nullptr, *other.root_) : nullptr;
    return *this;
}
// =^^^^^^^^^^^^^= AVLTree<T> ctor`s and optor`s  =^^^^^^^^^^^^^= 

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::find(AVLTree<T>::TreeNode* root, T val) const {
    if (!root) { return nullptr; }
    
    if (val == root->val_) { return root; }
    if (val < root->val_) { return find(root->left_, val); }
    return find(root->right_, val);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::min(AVLTree<T>::TreeNode* root) const {
    if (!root || !root->left_) { return root; }
    return min(root->left_);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::max(AVLTree<T>::TreeNode* root) const {
    if (!root || !root->right_) { return root; }
    return max(root->right_);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::pred(AVLTree<T>::TreeNode* node) const {
    if (!node) { return nullptr; }
    
    AVLTree<T>::TreeNode* par_min = node;
    AVLTree<T>::TreeNode* left_max = max(node->left_);
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

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::succ(AVLTree<T>::TreeNode* node) const {
    if (!node) { return nullptr; }
    
    AVLTree<T>::TreeNode* par_max = node;
    AVLTree<T>::TreeNode* right_min = min(node->right_);
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

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::insert(AVLTree<T>::TreeNode* root, T val) {
    if (!root) { return new TreeNode(val); }

    if (val < root->val_) {
        linked2Node(root, insert(root->left_, val), true);
    } else {
        linked2Node(root, insert(root->right_, val), false);
    }
    return rotationExecutor(root);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::removePrivate(T val) {
    TreeNode* target = find(root_, val);
    if (!target) { return root_; }

    AVLTree<T>::TreeNode* baby = target;
    if (target->left_ && target->right_) { 
        baby = min(target->right_); 
    } else if (target->right_) { 
        baby = target->right_; 
    } else if (target->left_) { 
        baby = target->left_; 
    }// baby = t OR min(t.r) OR t.r OR t.l

    target->val_ = baby->val_;
    AVLTree<T>::TreeNode* par_baby = baby->parent_;

    if (baby != target) {
        linked2Node(par_baby, baby->right_, (baby != target->right_));
    } else if (target != root_) {
        linked2Node(par_baby, baby->right_, (baby == par_baby->left_));
    }

    baby->left_ = nullptr;
    baby->right_ = nullptr;
    baby->parent_ = nullptr;
    delete baby;
    return bubbleRotationExecutor(par_baby);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::bubbleRotationExecutor(AVLTree<T>::TreeNode* root) {
    if (!root) { return nullptr; }

    AVLTree<T>::TreeNode* upd_root = rotationExecutor(root);
    return upd_root->parent_ ? bubbleRotationExecutor(upd_root->parent_) : upd_root;
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::rotationExecutor(AVLTree<T>::TreeNode* root) {
    if (!root) { return nullptr; }

    int balance = getBalance(root);
    if (balance == 2) {
        root = ((getBalance(root->right_) == -1) ? 
                bigLeftRotation(root) : 
                miniLeftRotation(root));
    } else if (balance == -2) {
        root = ((getBalance(root->left_) == 1)   ? 
                bigRightRotation(root) : 
                miniRightRotation(root));
    }

    root->height_ = getHeight(root);
    return root;
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::bigLeftRotation(AVLTree<T>::TreeNode* root) {
    // linked2Node(root, miniRightRotation(root->right_), false);
    miniRightRotation(root->right_);
    return miniLeftRotation(root);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::bigRightRotation(AVLTree<T>::TreeNode* root) {
    // linked2Node(root, miniLeftRotation(root->left_), true);
    miniLeftRotation(root->left_);
    return miniRightRotation(root);
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::miniLeftRotation(AVLTree<T>::TreeNode* root) {
    // root->height_--;
    // root->right_->height_++;
    
    // save pointers
    AVLTree<T>::TreeNode* old_par = root->parent_;
    AVLTree<T>::TreeNode* upd_root = root->right_;
    bool leftward = (old_par && old_par->left_ == root);
    
    upd_root->parent_ = old_par;
    linked2Node(root, upd_root->left_, false);
    linked2Node(upd_root, root, true);
    linked2Node(old_par, upd_root, leftward);
    
    root->height_ = getHeight(root);
    return upd_root;
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::miniRightRotation(AVLTree<T>::TreeNode* root) {
    // root->height_--;
    // root->left_->height_++;

    // save pointers
    AVLTree<T>::TreeNode* old_par = root->parent_;
    AVLTree<T>::TreeNode* upd_root = root->left_;
    bool leftward = (old_par && old_par->left_ == root);

    upd_root->parent_ = old_par;
    linked2Node(root, upd_root->right_, true);
    linked2Node(upd_root, root, false);
    linked2Node(old_par, upd_root, leftward);

    root->height_ = getHeight(root);
    return upd_root;
}

template <typename T>
int AVLTree<T>::getHeight(AVLTree<T>::TreeNode* root) const {
    if (!root) { return 0; }
    int lh = ((!root->left_)  ? 0 : root->left_->height_);     // height left
    int rh = ((!root->right_) ? 0 : root->right_->height_);    // height right
    return (lh > rh ? lh : rh) + 1;
}

template <typename T>
int AVLTree<T>::getBalance(AVLTree<T>::TreeNode* root) const {
    if (!root) { return 0; }
    return getHeight(root->right_) - getHeight(root->left_);
}

template <typename T>
void AVLTree<T>::linked2Node(AVLTree<T>::TreeNode* father, AVLTree<T>::TreeNode* baby, bool leftward) {
    if (!father) { return; }

    if (leftward) {
        father->left_ = baby;
    } else {
        father->right_ = baby;
    }
    
    if (baby) { baby->parent_ = father; } 
}

template <typename T>
void AVLTree<T>::recursiveDelete(AVLTree<T>::TreeNode* root) {
    if (!root) { return; }

    recursiveDelete(root->left_);
    recursiveDelete(root->right_);
    delete root;
}

template <typename T>
AVLTree<T>::TreeNode* AVLTree<T>::recursiveCopied(AVLTree<T>::TreeNode* father, const AVLTree<T>::TreeNode& other) {
    AVLTree<T>::TreeNode* node = new AVLTree<T>::TreeNode();

    node->val_ = other.val_;
    node->height_ = other.height_;

    node->parent_ = father;
    node->left_ = other.left_ ? recursiveCopied(node, *other.left_) : nullptr;
    node->right_ = other.right_ ? recursiveCopied(node, *other.right_) : nullptr;
    return node;
}

template <typename T>
void AVLTree<T>::printTree(AVLTree<T>::TreeNode* root, unsigned int counter) const {
    if (!root) { return; }
    std::string st(counter, '|');
    std::cout << st << ' ' << root->val_ << " {" << std::endl;
    std::cout << st << "left: " << std::endl;
    printTree(root->left_, counter+1);
    std::cout << st << "right: " << std::endl;
    printTree(root->right_, counter+1);
    std::cout << st << ' ' << " }" << std::endl;
}


template <typename T>
bool AVLTree<T>::find(T val) const {
    return (bool) find(root_, val);
}

template <typename T>
T AVLTree<T>::min() const {
    TreeNode* node = min(root_);
    return node ? node->val_ : T{}; 
}

template <typename T>
T AVLTree<T>::max() const {
    TreeNode* node = max(root_);
    return node ? node->val_ : T{}; 
}

template <typename T>
T AVLTree<T>::pred(T val) const {
    TreeNode* node = pred(find(root_, val));
    return node ? node->val_ : T{};
}

template <typename T>
T AVLTree<T>::succ(T val) const {
    TreeNode* node = succ(find(root_, val));
    return node ? node->val_ : T{};
}

template <typename T>
void AVLTree<T>::insert(T val) {
    root_ = insert(root_, val);
}

template <typename T>
void AVLTree<T>::remove(T val) {
    // root_ = remove(root_, val);
    root_ = removePrivate(val);
}

template <typename T>
bool AVLTree<T>::isEmpty() const {
    return (!root_);
} 

template <typename T>
int AVLTree<T>::getHeight() const {
    return getHeight(root_);
}

template <typename T>
void AVLTree<T>::printTree() const {
    printTree(root_, 0);
    std::cout << std::endl;
}

template <typename T>
AVLTree<T>::~AVLTree() {
    if (!root_) { return; }
    recursiveDelete(root_);
}
