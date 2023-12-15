#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// Define the stack structure
struct Stack {
    int top;
    int capacity;
    char* array;
};

// Function to create a new stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}

// Function to get the top element of the stack without popping it
char peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top];
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to get the precedence of an operator
int getPrecedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

// Function to convert infix expression to postfix
char* infixToPostfix(char* infixExpression) {
    struct Stack* stack = createStack(MAX_STACK_SIZE);
    char* postfixExpression = (char*)malloc(MAX_STACK_SIZE * sizeof(char));
    int i, j;

    for (i = 0, j = 0; infixExpression[i] != '\0'; i++) {
        char currentChar = infixExpression[i];

        if (isalnum(currentChar)) {
            postfixExpression[j++] = currentChar;
        } else if (currentChar == '(') {
            push(stack, currentChar);
        } else if (currentChar == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfixExpression[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                pop(stack); // Discard the '('
            }
        } else if (isOperator(currentChar)) {
            while (!isEmpty(stack) && getPrecedence(peek(stack)) >= getPrecedence(currentChar)) {
                postfixExpression[j++] = pop(stack);
            }
            push(stack, currentChar);
        }
    }

    // Pop any remaining operators from the stack
    while (!isEmpty(stack)) {
        postfixExpression[j++] = pop(stack);
    }

    postfixExpression[j] = '\0'; // Null-terminate the postfix expression
    free(stack);

    return postfixExpression;
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* postfixExpression) {
    struct Stack* stack = createStack(MAX_STACK_SIZE);
    int i;

    for (i = 0; postfixExpression[i] != '\0'; i++) {
        char currentChar = postfixExpression[i];

        if (isdigit(currentChar)) {
            push(stack, currentChar - '0');
        } else if (isOperator(currentChar)) {
            int operand2 = pop(stack);
            int operand1 = pop(stack);

            switch (currentChar) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }
    }

    int result = pop(stack);
    free(stack);

    return result;
}

int main() {
    char infixExpression[MAX_STACK_SIZE];
    printf("Enter an infix expression: ");
    scanf("%s", infixExpression);

    char* postfixExpression = infixToPostfix(infixExpression);
    printf("Postfix expression: %s\n", postfixExpression);

    int result = evaluatePostfix(postfixExpression);
    printf("Result of the expression: %d\n", result);

    free(postfixExpression);

    return 0;
}

