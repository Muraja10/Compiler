#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

typedef struct {
    char op;
    char arg1;
    char arg2;
    char result;
} Triple;

Triple triples[MAX_EXPRESSION_LENGTH];
int tripleCount = 0;

void addTriple(char op, char arg1, char arg2, char result) {
    triples[tripleCount].op = op;
    triples[tripleCount].arg1 = arg1;
    triples[tripleCount].arg2 = arg2;
    triples[tripleCount].result = result;
    tripleCount++;
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH];
    
    printf("Enter an expression: ");
    fgets(expression, MAX_EXPRESSION_LENGTH, stdin);
    
    int len = strlen(expression);
    
    char tempResult = 'T';
    
    for (int i = 0; i < len; i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            addTriple(expression[i], expression[i - 1], expression[i + 1], tempResult);
            expression[i - 1] = tempResult;
            for (int j = i; j < len - 2; j++) {
                expression[j] = expression[j + 2];
            }
            len -= 2;
            i--;
            tempResult++;
        }
    }
    
    printf("Triples:\n");
    for (int i = 0; i < tripleCount; i++) {
        printf("(%c, %c, %c, %c)\n", triples[i].op, triples[i].arg1, triples[i].arg2, triples[i].result);
    }
    
    return 0;
}

