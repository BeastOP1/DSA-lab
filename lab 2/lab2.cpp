#include<iostream>
using namespace std;

int maxValue(int a [], int l){
int max =0; //1
 for ( int i = 0 ;i<l; i++){   // n
    if(a[i] >max ){    // n
        max = a[i];
    }
 }
 return max; //1 
}

/*
Time Complexity

 f(n) = 1 + n + n + 1
 f(n)  = 2 + 2n
  removing constant
  f(n) = n

  Big-O(n)
*/

int main(){

    int arr[5] = { 9,18,8,1,6};
    int result = maxValue(arr, 5);
    cout<<"Max "<<result<<endl;

    return 0 ;
}
