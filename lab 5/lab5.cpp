#include<iostream>
using namespace std;
class Node;
class Node{
public:

int data;
Node *next;

    Node(){
        data = 0;
        next = nullptr;
    }
    Node(int d){
        this->data = d;
        this->next = nullptr;
    }

};
class LinkedList{
    Node *head;
    public:
    LinkedList(){
        this->head = nullptr;
    }

    void insertAtStart(int d){

        Node *newNode = new Node(d);
       newNode->next = head;
       head =newNode;

    }

    void insertAtLast(int d){
        Node *newNode = new Node(d);
        Node * temp = head;

        while(temp->next!= nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void insertAtAnyPosition(int d, int po){
        if(po < 1){
            cout<<"Invalid Positoin\n";
        }
        else if( po == 1){
            insertAtStart(d);
        }
        else{

            Node *newNode = new Node(d);
            Node *temp = head;

            for(int i = 1 ; i<po-1 ;i++){

                if(temp == nullptr){
                    cout<<"Invalid Postion";
                    break;
                }

                temp = temp->next;
            }

            newNode->next = temp->next;

            temp->next = newNode;
        }

    }

    void displayLinknedList(){
        Node *temp = head;

        while(temp != nullptr){

            cout<<temp->data;
            if(temp->next != nullptr){
                cout<<",";
            }
            temp = temp->next;
        }
        cout<<endl;
    }

    void displayFirstNode(){
      cout<<head->data<<endl;

    }
    void displaylastNode(){
      
      Node *temp = head;
      while(temp->next != nullptr){
        temp = temp->next;
      }
      cout<<temp->data<<endl;

    }

    void displayCenterNode(){
      Node *temp = head;
      int count = 0;
      while(temp != nullptr){
        temp= temp->next;
        count++;
      }
       temp = head;
      for(int i = 1 ; i<count; i++){
        temp = temp->next;
        if(i == count/2){
          cout<<temp->data<<endl;
          break;
        }
      }
    }
};
int main(){

    LinkedList l;
    l.insertAtStart(9);
    l.insertAtStart(93);
    l.insertAtLast(0);
    l.insertAtLast(88);
    l.insertAtAnyPosition(8,2);
    l.insertAtAnyPosition(18,2);
    cout<<"First Linked List Node : ";
    l.displayFirstNode();
    cout<<"Last LinkedList Node : ";
    l.displaylastNode();
    cout<<"Center linkedList : ";
    l.displayCenterNode();
    cout<<"LinkedList : ";
    l.displayLinknedList();
    

    return 0;
}