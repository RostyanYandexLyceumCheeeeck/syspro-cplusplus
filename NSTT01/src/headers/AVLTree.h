#pragma once

#include <iostream>
#include <string>


template <typename T>
class AVLTree {
private:
    class TreeNode {
        T val_;
        int height_ = 0;
        TreeNode* left_ = nullptr;
        TreeNode* right_ = nullptr;
        TreeNode* parent_ = nullptr;

        TreeNode() = default;
        TreeNode(T x): val_(x), height_(1) {}
        TreeNode(TreeNode&& other);
        TreeNode(const TreeNode& other): val_(other.val_), height_(other.height_), 
                                         left_(other.left_), right_(other.right_), parent_(other.parent_) {}
        
        TreeNode& operator=(TreeNode&& other);
        TreeNode& operator=(const TreeNode& other) = delete;
        
        ~TreeNode() = default;
        friend class AVLTree;
    };
    
    class Iterator {
        TreeNode* currentNode_ = nullptr;

    public:
        Iterator(TreeNode* node = nullptr) : currentNode_(node) {}

        Iterator& operator++();
        Iterator& operator++(int);
        
        T& operator*() { return currentNode_->val_; }
        T* operator->() { return &(currentNode_->val_); }

        bool operator==(const Iterator& other) const { return currentNode_ == other.currentNode_; }
        bool operator!=(const Iterator& other) const { return currentNode_ != other.currentNode_; }
};

    TreeNode* root_ = nullptr;

    TreeNode* find(TreeNode* root, T val) const;
    TreeNode* min(TreeNode* root) const;
    TreeNode* max(TreeNode* root) const;
    TreeNode* pred(TreeNode* node) const;
    TreeNode* succ(TreeNode* node) const;
    TreeNode* insert(TreeNode* root, T val);
    TreeNode* removePrivate(T val);

    TreeNode* bubbleRotationExecutor(TreeNode* root);
    TreeNode* rotationExecutor(TreeNode* root);
    TreeNode* bigLeftRotation(TreeNode* root);
    TreeNode* bigRightRotation(TreeNode* root);
    TreeNode* miniLeftRotation(TreeNode* root);
    TreeNode* miniRightRotation(TreeNode* root);
    
    int getHeight(TreeNode* root) const;
    int getBalance(TreeNode* root) const;
    void linked2Node(TreeNode* father, TreeNode* baby, bool leftward);

    void recursiveDelete(TreeNode* root);
    TreeNode* recursiveCopied(TreeNode* node, const TreeNode& other);

    void printTree(TreeNode* root, unsigned int counter) const;

public:
    AVLTree() = default;
    AVLTree(const AVLTree& other);
    AVLTree(AVLTree&& other);

    AVLTree& operator=(AVLTree&& other);
    AVLTree& operator=(const AVLTree& other);
    
    bool find(T val) const;
    T min() const;
    T max() const;
    T pred(T val) const;
    T succ(T val) const;
    void insert(T val);
    void remove(T val);

    bool isEmpty() const; 
    int getHeight() const;
    void printTree() const;
    
    Iterator begin() const { return Iterator(min(root_)); }
    Iterator end() const { return Iterator(nullptr); }

    ~AVLTree();
};

#include "AVLTree.ipp" 