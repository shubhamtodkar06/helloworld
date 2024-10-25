#include <stdio.h>
#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;

int queue[MAX_SIZE];
int front = -1, rear = -1;

void push(int x) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = x;
    printf("Pushed %d to stack\n", x);
}

// Pop function for stack
int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

void enqueue(int x) {
    if (rear >= MAX_SIZE - 1) {
        printf("Queue Full\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue[++rear] = x;
    printf("Enqueued %d to queue\n", x);
}

// Dequeue function for queue
int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue Empty\n");
        return -1;
    }
    int x = queue[front++];
    if (front > rear)
        front = rear = -1;
    return x;
}

int main() {

    push(1);
    push(2);
    push(3);
    printf("Popped element: %d\n", pop());
    printf("Popped element: %d\n", pop());

    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("Dequeued element: %d\n", dequeue());
    printf("Dequeued element: %d\n", dequeue());

    return 0;
}
