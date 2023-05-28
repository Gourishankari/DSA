#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct {
    int data[STACK_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == STACK_SIZE - 1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push %d\n", value);
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->data[stack->top--];
}

void saveStackToFile(Stack *stack, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to create file.\n");
        return;
    }
int i;
    for (i = stack->top; i >= 0; i--) {
        int number = stack->data[i];
        fprintf(file, "%d\n", number);
    }

    fclose(file);
    printf("Stack saved to %s\n", filename);
}

void readStackFromFile(Stack *stack, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    int value;
    while (fscanf(file, "%d", &value) == 1) {
        push(stack, value);
    }

    fclose(file);
    printf("Stack loaded from %s\n", filename);
}

int main() {
    Stack stack;
    initialize(&stack);

    int choice, value;
    char filename[50];

    while (1) {
        printf("\nStack Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Save to file\n");
        printf("4. Read from file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
            case 2:
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped value: %d\n", value);
                }
                break;
            case 3:
                printf("Enter the filename to save: ");
                scanf("%s", filename);
                saveStackToFile(&stack, filename);
                break;
            case 4:
                printf("Enter the filename to read: ");
                scanf("%s", filename);
                readStackFromFile(&stack, filename);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
