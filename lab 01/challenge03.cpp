#include <iostream>
#include<queue>
using namespace std;

void taskA(int a[], int n, int k) {
    int output[n-k+1];
    for(int i=0;i <=n-k; i++){
        int maximum = a[i];
        for(int j=i; j< i+k;j++){
            if(a[j] > maximum){
                maximum=a[j];
            }
        }
        output[i]=maximum;
    }
    for(int i=0; i<n-k +1; i++)
    {
        cout<<output[i]<<" ";
    }
}

void taskB(int a[], int n, int k) {
    int output[n - k + 1];
    deque<int> dq;

    for(int i =0;i< n;i++){
        if(!dq.empty() && dq.front()<= i - k){
            dq.pop_front();
        }
        while(!dq.empty() && a[dq.back()] <= a[i]){
            dq.pop_back();
        }
        dq.push_back(i);
        if(i >= k - 1){
            output[i-k+1] = a[dq.front()];
        }
    }
    for(int i=0;i < n-k+1;i++){
        cout << output[i] << " ";
    }
}

int main()
{
    int speed[7] = {4,3,5,8,6,9,2};
    int n=7;
    int k=3;
    taskA(speed, n, k);
    cout<<endl;
    taskB(speed, n, k);
    return 0;
}