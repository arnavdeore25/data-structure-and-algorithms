/*
Read n integers into an array, sorted in ascending order and possibly containing
duplicates, and then read a key. Write a function that uses binary search to return
the index of the first occurrence of the key, or -1 if it is absent.
Example: for [2, 4, 4, 4, 7, 9] and key 4, the output is 1.
*/

#include <stdio.h>

int binarySearch(int arr[], int n,int key) {
    int low=0;
    int high=n-1;
    int resultIndex=-1;

    while (low <= high) 
    {
        int mid=low+(high-low)/2;
        if (arr[mid] == key) 
        {
            resultIndex = mid;
            high=mid-1;
        } 
        else if (key < arr[mid]) {
            high= mid-1;
        } 
        else {
            low=mid+1;
        }
    }

    return resultIndex;
}

int main() {
    int arr[100];
    int n;
    int searchKey;

    printf("Enter total no of elements you want to add to array: ");
    scanf("%d", &n);

    printf("Enter array elements in sorted order:\n");
    for (int i=0; i <n;i++) {
        printf("Enter Value for element %d: ",i+1);
        scanf("%d", &arr[i]);
    }

    printf("\nArray elements: ");
    for (int i=0; i<n; i++) {
        printf("%d ",arr[i]);
    }

    printf("\nEnter searchKey: ");
    scanf("%d",&searchKey);
    int resultIndex = binarySearch(arr,n,searchKey);

    if (resultIndex!=-1) {
        printf("The value was found at position %d\n",resultIndex);
    } 
    else {
        printf("Data not found\n");
    }

    return 0;
}