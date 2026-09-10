#include<iostream>
#include<stack>
using namespace std;

void directApproach(int a[], int n) {
    int output[8] = {0};
    for(int i =0; i<n; i++) {
        int counter = 1;
        for(int j = i+1; j<n; j++) {
            if(a[j]>a[i]) {
                output[i] = counter;
                break;
            }
            counter++;
        }
    }
    for(int i=0; i<n; i++) {
        cout<<output[i]<<endl;
    }
}

void singlePassApproach(int a[],int ans[],int n)
{
    stack<int> s;
    for(int i=0;i<n;i++) {
        while(!s.empty() && a[i] > a[s.top()]) {
            int previous = s.top();
            s.pop();
            ans[previous] = i - previous;
        }
        s.push(i);
    }
}
int main(){
    int temp[8] = {73, 74, 75, 71, 69, 72, 76, 73};
    int n = 8;
    int output[8] = {0};
    directApproach(temp, n);
    cout<<endl;
    singlePassApproach(temp, output, n);
    for(int i=0; i<n; i++) {
        cout<<output[i]<<endl;
    }
   return 0;
}