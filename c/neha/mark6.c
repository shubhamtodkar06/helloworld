#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Stack {
    struct Node *top;
};

struct Queue {
    struct Node *front;
    struct Node *rear;
};

// Function to create a new node (used by both stack and queue)
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Stack operations
void push(struct Stack *stack, int data) {
    struct Node *newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(struct Stack *stack) {
    if (stack->top == NULL) {
        printf("Stack is empty.\n");
        return -1;
    }
    struct Node *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

void displayStack(struct Stack *stack) {
    struct Node *temp = stack->top;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Queue operations
void enqueue(struct Queue *queue, int data) {
    struct Node *newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(struct Queue *queue) {
    if (queue->front == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }
    struct Node *temp = queue->front;
    int data = temp->data;
    queue->front = temp->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

void displayQueue(struct Queue *queue) {
    struct Node *temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    stack.top = NULL;
    struct Queue queue;
    queue.front = queue.rear = NULL;
    int choice, data;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Display Stack\n4. Enqueue\n5. Dequeue\n6. Display Queue\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(&stack, data);
                break;
            case 2:
                data = pop(&stack);
                if (data != -1) {
                    printf("Popped element: %d\n", data);
                }
                break;
            case 3:
                printf("Stack: ");
                displayStack(&stack);
                break;
            case 4:
                printf("Enter data to enqueue: ");
                scanf("%d", &data);
                enqueue(&queue, data);
                break;
            case 5:
                data = dequeue(&queue);
                if (data != -1) {
                    printf("Dequeued element: %d\n", data);
                }
                break;
            case 6:
                printf("Queue: ");
                displayQueue(&queue);
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
