#ifndef AVLTree_H_
#define AVLTree_H_

class AVLTree {
private:
    struct TreeNode {
        int val;
        int height;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(int x): val(x), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
    };

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
    using Node = TreeNode;

    AVLTree();
    AVLTree(Node* root);

    Node* find(int val);
    Node* min();
    Node* max();
    Node* pred(Node* node);
    Node* succ(Node* node);
    void insert(int val);
    void remove(int val);

    bool isEmpty(); 
    int getHeight();
    void printTree();

    Node* createNode(int v);
    int getValueNode(Node* node);
    void setValueNode(Node* node, int v);

    ~AVLTree();
};


#endif // AVLTree_H_