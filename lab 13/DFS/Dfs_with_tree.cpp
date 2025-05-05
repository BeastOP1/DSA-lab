#include<iostream>

using namespace std;

struct TreeNode
{
    int value;
    TreeNode* left , *right;

    TreeNode(int v = -1){
        value = v;
        left = nullptr;
        right = nullptr;
    }

};


class DepthFrstSearchTree
{
private:
TreeNode* root;

TreeNode* insertNode(TreeNode* node , int value){
    if(node ==nullptr){
        return new TreeNode(value);
    }

    if(value <node->value){
        node->left = insertNode(node->left, value);

    }else{
        node->right = insertNode(node->right, value);
    }
    return node;
}


void preOrder(TreeNode* node){
    if(node != nullptr){
        cout <<node->value<<" ";

        preOrder(node->left);
        preOrder(node->right);
    }
}
public:
    DepthFrstSearchTree(){

        root = nullptr;
    }
    ~DepthFrstSearchTree(){}



    void insert(int value){
        root = insertNode(root, value);
    }


    void display(){
        preOrder(root);
        cout<<endl;
    }

};


int main(){

    DepthFrstSearchTree dfs;

    int values[]  = {7,4,8,9, 3,2  };
    
    for(int value : values){
        dfs.insert(value);
    }

    cout<<"DFS Travesal of Tree (Pre-Order):\n";
    dfs.display();


    return 0;
}