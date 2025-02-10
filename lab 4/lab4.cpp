
#include<iostream>
using namespace std;
class Node{
    public:
    int data;
    Node* next;
     Node(int d = 0){
        data = d;
        this->next = nullptr;
     }
};

class LinkedList{
    Node* head ;
    public:

    LinkedList(){
        head = nullptr;
    }
    //Insert at Head
    void insertAtStart(int d){
        Node* newNode = new Node(d);
        newNode->next = head;
        head = newNode;
        
    }
    //Insert At Last 
    void insertAtLast(int d){
        Node* newNode = new Node(d);

        Node *temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;

    }
    void insertAtPosition(int d, int position){

        if(position < 1){
            cout<<"InValid Position.\n";
        }
        else if(position == 1){
            insertAtStart(d);
        }
        else {
        Node* newNode = new Node(d);

        Node* temp = head;
        for( int i =1 ; i<position-1; i++){

            if(temp ==  nullptr){
                cout<<"InValid Position.\n";
                break;
            }
            temp= temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;

    }

    }
    void displayLinkedList(){

        Node *temp2 = head;

        while(temp2 != nullptr){
            cout<<temp2->data;
             if(temp2->next != nullptr){
               cout<<",";
            }
            temp2 = temp2->next;
           
        }
        cout<<endl;
    }


};
int main(){
    LinkedList l;

    l.insertAtStart(23);
    l.insertAtLast(8);
    l.insertAtPosition(14,1);
    cout<<"Linked List : ";
    l.displayLinkedList();

    return 0;
}