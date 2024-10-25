#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

int countNodes(); // Corrected declaration

void insertAtFront(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

void insertAtEnd(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertInMiddle(int data, int position) {
    if (position < 1 || position > countNodes() + 1) {
        printf("Invalid position.\n");
        return;
    }
    if (position == 1) {
        insertAtFront(data);
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    struct Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void display() {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void displayReverse(struct Node* temp) {
    if (temp == NULL) {
        return;
    }
    displayReverse(temp->next);
    printf("%d ", temp->data);
}

void reverse() {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

int countNodes() {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int main() {
    insertAtFront(10);
    insertAtEnd(20);
    insertInMiddle(30, 2);

    printf("Display: ");
    display();

    printf("Display Reverse: ");
    displayReverse(head);
    printf("\n");

    reverse();
    printf("Reversed List: ");
    display();

    return 0;
}
