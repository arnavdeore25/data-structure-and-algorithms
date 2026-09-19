/*
Time Complexity: O(n)
Space Complexity: O(n)
*/

#include<stdio.h>
#include<stdlib.h>
 
typedef struct node {
    int data;
    struct node *ptr;
}node;  
    
typedef struct {
    int *data;
    int top, capacity;
}stack;
     
int pop(stack *stk) {
    if(stk->top == -1) {
        return -1;
    }
    
    return stk->data[stk->top--];
}
    
void main() {
     
//Array Define
     
    int a[100], n;
     
    printf("Enter noof values you want to add: ");
    scanf("%d", &n);
   
    if(n < 0 || n > 100) {
        printf("Invalid number of elements.");
        return;
    }
   
    if(n == 0) {
        printf("No elements entered.");
        return;
    }
   
    for(int i = 0; i < n; i++) {
        printf("Enter element: ");
        scanf("%d", &a[i]);
    }
    
    //Array Display
   
    printf("\nArray:");
   
    for(int i = 0; i < n; i++) {
        printf("\n%d", a[i]);
    }
    
    printf("\n");
    
//Linked List
    node *head = NULL;
    node *temp = NULL;
   
    head = malloc(sizeof(node));
   
    if(head == NULL) {
        printf("Memory allocation failed.");
        return;
    }
   
    head->data = a[0];
    head->ptr = NULL;
    temp = head;
   
    for(int i = 1; i < n; i++) {
   
        node *newNode = malloc(sizeof(node));
  
        if(newNode == NULL) {
            printf("Memory allocation failed.");
   
            temp = head;
   
            while(temp != NULL) {
                node *deleteNode = temp;
                temp = temp->ptr;
                free(deleteNode);
            }
   
            return;
        }
   
        newNode->data = a[i];
        newNode->ptr = NULL;
  
        temp->ptr = newNode;
        temp = newNode;
    }
   
    printf("\nLinked List:");
   
    temp = head;
   
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->ptr;
    }
   
    printf("NULL");
   
    stack stk;
   
    stk.capacity = n;
    stk.top = -1;
   
    stk.data = malloc(stk.capacity * sizeof(int));
   
    if(stk.data == NULL) {
        printf("\nMemory allocation failed.");
   
        temp = head;
    
        while(temp != NULL) {
            node *deleteNode = temp;
            temp = temp->ptr;
            free(deleteNode);
        }
   
        return;
    }
   
    temp = head;
   
    while(temp != NULL) {
        stk.data[++stk.top] = temp->data;
        temp = temp->ptr;
    }
   
    printf("\nStack:");
   
    for(int i = stk.top; i >= 0; i--) {
        printf("\n%d", stk.data[i]);
    }
   
    temp = head;
   
    int flag = 1;
  
    while(temp != NULL) {
   
        if(temp->data != pop(&stk)) {
            flag = 0;
            break;
        }
   
        temp = temp->ptr;
    }
   
    if(flag == 1) {
        printf("\nYes it is Palindrome");
    }
    else {
        printf("\nNot Palindrome");
    }
   
    free(stk.data);
   
    temp = head;
   
    while(temp != NULL) {
        node *deleteNode = temp;
        temp = temp->ptr;
        free(deleteNode);
    }
}