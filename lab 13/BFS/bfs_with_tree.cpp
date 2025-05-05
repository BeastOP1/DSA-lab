#include <iostream>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

struct QueueNode {
    TreeNode* treeNode;
    QueueNode* next;
    QueueNode(TreeNode* node) : treeNode(node), next(nullptr) {}
};

class Queue {
private:
    QueueNode *front, *rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    
    void enqueue(TreeNode* node) {
        QueueNode* newNode = new QueueNode(node);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    TreeNode* dequeue() {
        if (front == nullptr) return nullptr;
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        TreeNode* node = temp->treeNode;
        delete temp;
        return node;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
};

void bfs_tree(TreeNode* root) {
    if (root == nullptr) return;
    
    Queue q;
    q.enqueue(root);
    
    while (!q.isEmpty()) {
        TreeNode* node = q.dequeue();
        cout << node->value << " ";
        
        if (node->left != nullptr) {
            q.enqueue(node->left);
        }
        if (node->right != nullptr) {
            q.enqueue(node->right);
        }
    }
}


int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    cout << "BFS Traversal of Tree:\n";
    bfs_tree(root);
    cout << endl;
 
    return 0;
}
