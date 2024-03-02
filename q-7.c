#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node*next;
};
struct node* rear=NULL;
struct node*front=NULL;
int isempty(){
    if(rear==NULL && front==NULL){
        return 1;
    }
    else{
        return 0;
    }
}
int sizeq(){
    struct node*ptr=front;
    int count=0;
    while(ptr!=NULL){
        count++;
        ptr=ptr->next;
    }
    return count;
}
void enqueue(int val){
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->data=val;
    temp->next=NULL;
    if(rear==NULL && front==NULL){
        rear=temp;
        front =temp;
    }
    else{
        rear->next=temp;
        rear=temp;
    }
    
}
void dequeue(){
    if(isempty()){
        printf("queue is empty\n");
    }
    else{
        struct node*ptr=front;
        front=front->next;
        free(ptr);
    }
}
void display(){
    if(isempty()){
        printf("nothing to be displayed\n");
    }
    else{
        struct node*ptr=front;
        while(ptr!=NULL){
            printf("%d ",ptr->data);
            ptr=ptr->next;
        }
        printf("\n");
    }
}
int main(){
    display();
    enqueue(1);
    enqueue(2);
    enqueue(3);
    display();
    int count=sizeq();
    printf("%d is the count\n",count);
    dequeue();
    display();
}