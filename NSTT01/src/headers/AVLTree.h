#ifndef AVLTree_H_
#define AVLTree_H_

class AVLTree {
public:
    struct TreeNode;

    AVLTree();
    AVLTree(TreeNode* root);

private:
    TreeNode* root_;

    TreeNode* find(TreeNode* root, int val);
    TreeNode* min(TreeNode* root);
    TreeNode* max(TreeNode* root);
    TreeNode* predPrivate(TreeNode* node);
    TreeNode* succPrivate(TreeNode* node);
    TreeNode* insert(TreeNode* root, int val);
    TreeNode* remove(TreeNode* root, int val);

    TreeNode* bubbleRotationExecutor(TreeNode* root);
    TreeNode* rotationExecutor(TreeNode* root);
    TreeNode* bigLeftRotation(TreeNode* root);
    TreeNode* bigRightRotation(TreeNode* root);
    TreeNode* miniLeftRotation(TreeNode* root);
    TreeNode* miniRightRotation(TreeNode* root);
    
    int getHeight(TreeNode* root);
    int getBalance(TreeNode* root);
    void linked2Node(TreeNode* father, TreeNode* baby, bool leftward);

    void rmTree(TreeNode* root);

    void printTree(TreeNode* root, unsigned int counter);

public:
    struct TreeNode {
        int val;
        int height;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(int x): val(x), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    TreeNode* find(int val);
    TreeNode* min();
    TreeNode* max();
    TreeNode* pred(TreeNode* node);
    TreeNode* succ(TreeNode* node);
    void insert(int val);
    void remove(int val);

    bool isEmpty(); 
    int getHeight();
    void printTree();

    ~AVLTree();
};


#endif // AVLTree_H_