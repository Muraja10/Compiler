#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_LENGTH 100

// Production rules
char *production[] = {
    "E->E+E",
    "E->E*E",
    "E->(E)",
    "E->i"
};

// Parsing table
char parsingTable[4][6][4] = {
    {"-", "-", "s3", "s4", "-", "-"},
    {"s5", "-", "-", "-", "s6", "-"},
    {"-", "-", "s3", "s4", "-", "-"},
    {"-", "r3", "r3", "-", "r3", "A"}
};

// Stack data structure
typedef struct {
    char symbol;
    int state;
} StackItem;

StackItem stack[MAX_STACK_SIZE];
int top = -1;

void push(char symbol, int state) {
    if (top < MAX_STACK_SIZE - 1) {
        top++;
        stack[top].symbol = symbol;
        stack[top].state = state;
    } else {
        printf("Error: Stack overflow.\n");
        return;
    }
}

void pop() {
    if (top >= 0) {
        top--;
    } else {
        printf("Error: Stack underflow.\n");
        return;
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    int currentState = 0;
    int inputIndex = 0;

    printf("Enter an expression (e.g., 'i+i*i'): ");
    scanf("%s", input);

    strcat(input, "$");

    push('$', 0);

    bool parsingSuccessful = true;

    while (1) {
        char currentInput = input[inputIndex];
        char currentSymbol = stack[top].symbol;

        int currentInputIndex = -1;
        int currentSymbolIndex = -1;

        if (currentInput == 'i') {
            currentInputIndex = 0;
        } else if (currentInput == '+') {
            currentInputIndex = 1;
        } else if (currentInput == '*') {
            currentInputIndex = 2;
        } else if (currentInput == '(') {
            currentInputIndex = 3;
        } else if (currentInput == ')') {
            currentInputIndex = 4;
        } else if (currentInput == '$') {
            currentInputIndex = 5;
        }

        if (currentSymbol == 'E') {
            currentSymbolIndex = 0;
        }

        char action = parsingTable[currentState][currentInputIndex][0];
        char nextSymbol = parsingTable[currentState][currentInputIndex][1];

        if (action == 's') {
            push(currentInput, nextSymbol - '0');
            currentState = nextSymbol - '0';
            inputIndex++;
        } else if (action == 'r') {
            int ruleIndex = nextSymbol - '0';
            char *productionRule = production[ruleIndex];
            int popCount = strlen(productionRule) - 3;
            for (int i = 0; i < popCount; i++) {
                pop();
            }
            currentSymbol = stack[top].symbol;
            currentState = stack[top].state;
            char nonTerminal = productionRule[0];
            if (nonTerminal == 'E') {
                currentSymbolIndex = 0;
            }
            char nextState = parsingTable[currentState][currentSymbolIndex][0];
            push(nonTerminal, nextState - '0');
        } else if (action == 'A') {
            break; // Accept
        } else {
            parsingSuccessful = false;
            printf("Error: Parsing failed.\n");
            break;
        }
    }

    if (parsingSuccessful) {
        printf("Accept: Parsing successful.\n");
    }

    return 0;
}

