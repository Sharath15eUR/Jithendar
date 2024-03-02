#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 5
int queue[size];
int rear=-1,front=-1;
int isempty(){
    if(rear==-1 && front==-1){
        return 1;
    }
    else{
        return 0;
    }
}
int isfull(){
    if(rear==size-1){
        return 1;
    }
    else{
        return 0;
    }
}
int peek(){
    if(rear==-1 && front==-1){
        return 0;
    }
    return queue[front];
}
void enqueue(int data){
    if(rear==size-1){
        printf("queue is empty\n");
    }
    if(front==-1){
        front=0;
    }
    rear++;
    queue[rear]=data;
}
void dequeue(int data){
    if(rear==-1&&front==-1){
        printf( "queue is empty\n");
    }
    queue[front]=0;
    front++;
    if(front >rear){
        front=-1;
        rear=-1;
    }
}
void display(){
    if(rear==-1 && front==-1){
        printf("queue is empty\n");
    }
    else{
        for(int i=front;i<=rear;i++){
            printf("%d ",queue[i]);
        }
    }
    printf("\n");
}
int sizeq(){
    if(rear==-1 && front==-1){
        printf("queue is empty");
    }
    else{
        return rear+front-1;
    }
}
int main(){
    if(isempty()){
        printf("queue is empty\n");
    }
    if(isfull()){
        printf("queue is full\n");
    }
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    display();
    dequeue(1);
    display();
    int first=peek();
    printf("%d\n",first);
    int l=sizeq();
    printf("%d\n",l);
}