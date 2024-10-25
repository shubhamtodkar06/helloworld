#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE 40

int stack[SIZE];
int top = -1;

int pop() {
    if (top == -1) {
        printf("Stack is empty!\n");
        exit(-1);
    }
    return stack[top--];
}

void push(int n) {
    if (top >= SIZE - 1) {
        printf("Stack is full!\n");
        exit(-1);
    }
    stack[++top] = n;
}

int main() {
    char postfix[SIZE];
    int i, a, b, result;

    printf("\nEnter a postfix expression: ");
    scanf("%s", postfix);

    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            push(ch - '0');
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            b = pop();
            a = pop();
            switch (ch) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        printf("Division by zero error!\n");
                        exit(-1);
                    }
                    result = a / b;
                    break;
                default:
                    printf("Invalid operator: %c\n", ch);
                    exit(-1);
            }
            push(result);
        } else {
            printf("Invalid character: %c\n", ch);
            exit(-1);
        }
    }

    if (top != 0) {
        printf("Invalid postfix expression: too many operands.\n");
        exit(-1);
    }

    int pEval = pop();
    printf("\nThe postfix evaluation is: %d\n", pEval);
    return 0;
}
