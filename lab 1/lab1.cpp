
#include<iostream>
using namespace std;
int main(){

    int a = 1;
    int *ptr = &a;


    cout<<"Before\n";
    cout<<" A : "<<a<<endl;
    cout <<" *Ptr : "<<*ptr<<endl;
    cout<<"After\n";
    *ptr  = 9;
    cout<<" A : "<<a<<endl;
    cout <<" *Ptr : "<<*ptr<<endl;
    delete ptr;
    ptr  = nullptr;
    
    return 0;
}

