
#include <iostream>
using namespace std;

/*
Trees is basically have multiple Nodes but BST is have only two Node left and right

BST have two rules ...the Next newNode will be linked if its samller than the root Node it will linked  on left side and if its bigger than the root Node it will linked on right side
BST Have
1--- insert ,
3--- search
4--- update
*/
struct Node
{
    int key;
    Node *left, *right;
    Node(int k= 0);

    ~Node(){
        delete left , right;
        left = nullptr;
        right = nullptr;
    }
};
Node::Node(int k )
{
    {
        key = k;
        left = right = nullptr;
    }
}

class Binary_search_tree
{
private:
    Node *root;

Node* deleteNode(Node* rootNode , int k){
    /*
    
        7
      5   8
    4   6     90
    */

    if(!rootNode ) return nullptr; //Base Case 

    //search for Node
    if(k <rootNode->key){
        rootNode->left = deleteNode(rootNode->left,k);
    }else if(k > rootNode->key){
        rootNode->right = deleteNode(rootNode->right,k);

    }else {

        //Node found -now delete it
        //case 1 : No Child or one child
        if(!rootNode->left){
            Node* temp = rootNode->right;
            delete rootNode;
            return temp;    
        }else if(!rootNode->right) {

            Node* temp = rootNode->left;
            delete rootNode;
            return temp;
        }

        //case 3: Two Children 
        Node* successor = findMin(rootNode->right);
        rootNode->key = successor->key;
        rootNode->right = deleteNode(rootNode->right,successor->key);
    }
    return rootNode;
    }   

public:
    Binary_search_tree(){
        root = nullptr;
    }
    ~Binary_search_tree(){};

    void insert(int k)
    {
        Node *newNode = new Node(k); // 10

        if (root != nullptr)
        {

            Node *temp = root;
            while (true)
            {

                if (k <temp->key)
                {
                    if(temp->left == nullptr){
                         temp->left = newNode;
                         break;
                    }
                    // Left side
                    temp = temp->left;
                }
                else
                {
                    // RIght side
                    if(temp->right == nullptr){
                        temp->right = newNode;
                        break;

                    }
                    temp = temp->right;
                }
            }


            // cout<<"Added Successfully.\n";
        }
        else
        {

            root = newNode;
        }
    }


    void delete_Node(int k)
    {        
        root = deleteNode(root,k);
       
    }

    Node* findMin(Node* node ){

        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;

    }
    void search(int k)
    {

        if (root != nullptr)
        {

            Node *temp = root;
            while (temp != nullptr && temp->key != k  )
            {

                if (k > temp->key)
                {
                    temp = temp->right;

                }else if(temp == nullptr){
                    break;
                }
                else
                {
                    temp = temp->left;
                }

            }

            if (temp->key == k && temp != nullptr)
            {

                cout << "\nFound Out. \n Address : " << temp;
            }
            else
            {
                cout << "Not Found Out.\n";
            }
        }
        else
        {
            cout << "Tree is Empty.\n";
        }
    }

    void update(int d, int newValue)
    {

        Node *temp = root;

        while (temp->key != d)
        {
            if (d > temp->key)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        temp->key = newValue;
        if (temp->key == newValue)
        {
            cout << "Value Updated Successfully.\n";
        }
        else
        {
            cout << "Error While Updating the Value.\n";
        }
    }

    void inorder(Node* root)
    {
     
    
        if(root == nullptr) {
            return ;
        }else {
            inorder(root->left);
            cout<<root->key<<" -> ";

            inorder(root->right);
        }
        
        
    }

    void preOrder(Node* root){

        if(root == nullptr){
            return ;
        }else{
            preOrder(root->left);
            postOder(root->right);
            cout<<root->key<<" -> ";
        }
    }

    void postOder(Node* root){

        if(root == nullptr){
            return ;
        }else {

            cout<<root->key <<" -> ";
            postOder(root->left);
            postOder(root->right);

        }
    }

    Node* getRoot(){
        return root;
    }
};




int main()
{

    int keys[5] = { 90,2 ,8,7,91};
    Binary_search_tree bst;

    for(int key : keys){
        bst.insert(key);
    }

    cout<<"Pre-order Traverse : ";
    bst.preOrder(bst.getRoot());
    cout<<endl;

    bst.delete_Node(8); //Deleting 8 key 

    cout<<endl;

    cout<<"Pre-order Traverse : ";
    bst.preOrder(bst.getRoot());
    cout<<endl;




}