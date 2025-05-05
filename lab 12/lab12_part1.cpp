#include<iostream>
using namespace std;

struct Node {
    int key, height;
    Node *left, *right;

    Node(int k = 0) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class Avl {
    Node* root;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* t2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = t2;

        // Update heights
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        //return a new noot
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* t2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = t2;

        // Update heights
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        //return a new noot
        return y;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNodeHelper(Node* node, int key) {
        if (node == nullptr) return node;

        if (key < node->key)
            node->left = deleteNodeHelper(node->left, key);
        else if (key > node->key)
            node->right = deleteNodeHelper(node->right, key);
        else {
            // Node with only one child or no child
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;

                // No child case
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } 
                else { // One child case
                    *node = *temp; // Copy the contents
                }
                delete temp;
            } 
            else {
                // Node with two children: Get inorder successor
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNodeHelper(node->right, temp->key);
            }
        }

        // If the tree had only one node then return
        if (node == nullptr) return node;

        // Update height
        node->height = 1 + max(height(node->left), height(node->right));

        // Rebalance the node
        int balance = getBalancedFactor(node);

        // Left Left Case
        if (balance > 1 && getBalancedFactor(node->left) >= 0)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 && getBalancedFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalancedFactor(node->right) <= 0)
            return leftRotate(node);

        // Right Left Case
        if (balance < -1 && getBalancedFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* insertNode(Node* node, int key) {
        // Perform the normal BST insertion
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else // Equal keys are not allowed in BST 
            return node;
        // Update height of this ancestor node 
        node->height = 1 + max(height(node->left), height(node->right));

        // Get the balance factor of this ancestor node 
        int balance = getBalancedFactor(node);

        
        // If this node becomes unbalanced, 
        // then there are 4 cases 

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the (unchanged) node pointer 

        return node;
    }

public:
    Avl() {
        root = nullptr;
    }

    int getBalancedFactor(Node* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    void insert(int key) {
        root = insertNode(root, key);
    }

    
    void deleteNode(int key) {
        root = deleteNodeHelper(root, key);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << " -> ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    Node* getRoot() const { return root; }
};

int main() {

    int nodes[] = { 10,20,30,40,50,25};
    Avl avl;
    
    for (int key: nodes)
    {
     
    avl.insert(key);
    }

    cout << "Preorder traversal before deletion: ";
    avl.preorder(avl.getRoot());
    cout << endl;

    avl.deleteNode(30); // Delete node with key 30

    cout << "Preorder traversal after deletion: ";
    avl.preorder(avl.getRoot());
    cout << endl;

    return 0;
}