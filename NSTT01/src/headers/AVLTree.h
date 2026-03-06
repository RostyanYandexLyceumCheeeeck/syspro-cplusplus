#ifndef AVLTree_H_
#define AVLTree_H_

class AVLTree {
private:
    class TreeNode {
        int val_ = 0;
        int height_ = 0;
        TreeNode* left_ = nullptr;
        TreeNode* right_ = nullptr;
        TreeNode* parent_ = nullptr;

        TreeNode() = default;
        TreeNode(int x): val_(x), height_(1) {}
        
        TreeNode(TreeNode&& other);
        TreeNode(const TreeNode& other): val_(other.val_), height_(other.height_), 
                                         left_(other.left_), right_(other.right_), parent_(other.parent_) {}
        
        TreeNode& operator=(TreeNode&& other);
        TreeNode& operator=(const TreeNode& other) = delete;
        
        ~TreeNode() = default;
        friend class AVLTree;
    };

    TreeNode* root_ = nullptr;

    TreeNode* find(TreeNode* root, int val);
    TreeNode* min(TreeNode* root);
    TreeNode* max(TreeNode* root);
    TreeNode* predPrivate(TreeNode* node);
    TreeNode* succPrivate(TreeNode* node);
    TreeNode* insert(TreeNode* root, int val);
    TreeNode* removePrivate(int val);

    TreeNode* bubbleRotationExecutor(TreeNode* root);
    TreeNode* rotationExecutor(TreeNode* root);
    TreeNode* bigLeftRotation(TreeNode* root);
    TreeNode* bigRightRotation(TreeNode* root);
    TreeNode* miniLeftRotation(TreeNode* root);
    TreeNode* miniRightRotation(TreeNode* root);
    
    int getHeight(TreeNode* root);
    int getBalance(TreeNode* root);
    void linked2Node(TreeNode* father, TreeNode* baby, bool leftward);

    void printTree(TreeNode* root, unsigned int counter);

public:
    AVLTree() = default;
    AVLTree(AVLTree&& other);
    AVLTree(const AVLTree& other);

    AVLTree& operator=(AVLTree&& other);
    AVLTree& operator=(const AVLTree& other);
    
    bool find(int val);
    int min();
    int max();
    int pred(int val);
    int succ(int val);
    void insert(int val);
    void remove(int val);

    bool isEmpty(); 
    int getHeight();
    void printTree();
    
    void AVLTree::recursiveDelete(AVLTree::TreeNode* root);
    AVLTree::TreeNode* recursiveCopied(AVLTree::TreeNode* node, const AVLTree::TreeNode& other);
    ~AVLTree();
};


#endif // AVLTree_H_