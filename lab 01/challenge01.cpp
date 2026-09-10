#include <iostream>
using namespace std;
int approach1(int a[], int n) {
    int flag;
    for(int i=0; i< 7; i++) {
        if((a[i]>a[i-1] && a[i]>a[i+1]) || 
           (a[i] > a[i+1] && a[i-1] == -1 ) || 
           (a[i+1]==7 && a[i] > a[i-1] )) {
            flag = i;
            break;
        }
    }
    return flag;
}
int approach2(int a[], int n) {
    int mid, low = 0, high=n-1;
     while(low<high) {
        mid = low +(high-low)/2;

        if(a[mid] < a[mid+1]) {
            low = mid+1;
        }
        else {
            high = mid;
        }
    }
    return low;
}
int main()
{
    int output;
    int a[10] = {1, 5, 2, 8, 3, 9, 4};
    int n = 7;
    cout<<"Elements of Array: "<<endl;
    for(int i=0; i<7; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    cout<<"Output from Approach 1"<<endl;
    output = approach1(a, n);
    cout<<"Output: "<<output;
    cout<<endl<<"Output from Approach 2"<<endl;
    output = approach2(a, n);
    cout<<"Output: "<<output;
    
    return 0;
}