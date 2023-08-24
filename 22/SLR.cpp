#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_LENGTH 100

typedef struct {
    char symbol;
    int state;
} StackItem;

StackItem stack[MAX_STACK_SIZE];
int top = -1;

int action[5][4] = {
    {1, -1, -1, 2}, // State 0
    {3, 4, -1, -1}, // State 1
    {-1, -1, -1, -1}, // State 2 (Accept)
    {1, -1, -1, 2}, // State 3
    {-1, -1, 5, -1} // State 4
};

char *input;
int inputIndex = 0;

void push(char symbol, int state) {
    if (top < MAX_STACK_SIZE - 1) {
        top++;
        stack[top].symbol = symbol;
        stack[top].state = state;
    } else {
        printf("Error: Stack overflow.\n");
        exit(1);
    }
}

void pop(int count) {
    if (top >= count - 1) {
        top -= count;
    } else {
        printf("Error: Stack underflow.\n");
        exit(1);
    }
}

int getTerminalIndex(char terminal) {
    switch (terminal) {
        case '+':
            return 0;
        case '*':
            return 1;
        case 'i':
            return 2;
        case '$':
            return 3;
        default:
            return -1;
    }
}

int main() {
    input = (char *)malloc(MAX_INPUT_LENGTH);
    printf("Enter an expression (e.g., 'i+i*i$'): ");
    scanf("%s", input);
    strcat(input, "$"); // Append $ to mark the end of input

    push('$', 0);

    while (1) {
        int terminalIndex = getTerminalIndex(input[inputIndex]);
        int currentState = stack[top].state;
        int nextAction = action[currentState][terminalIndex];

        if (nextAction == -1) {
            printf("Error: Parsing failed.\n");
            break;
        } else if (nextAction == 0) {
            printf("Accept: Parsing successful.\n");
            break;
        } else if (nextAction > 0) {
            push(input[inputIndex], nextAction);
            inputIndex++;
        } else {
            int reduceProduction = -nextAction;
            switch (reduceProduction) {
                case 1:
                    pop(3); // E -> E + T
                    push('E', action[stack[top].state][0]);
                    break;
                case 2:
                    pop(3); // E -> T
                    push('E', action[stack[top].state][0]);
                    break;
                case 3:
                    pop(3); // T -> T * F
                    push('T', action[stack[top].state][1]);
                    break;
                case 4:
                    pop(3); // T -> F
                    push('T', action[stack[top].state][1]);
                    break;
                default:
                    printf("Error: Invalid production.\n");
                    exit(1);
            }
        }
    }

    free(input);
    return 0;
}

