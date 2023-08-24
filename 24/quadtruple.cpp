#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

typedef struct {
    char op;
    char arg1;
    char arg2;
    char result;
} Quadruple;

Quadruple quadruples[MAX_EXPRESSION_LENGTH];
int quadrupleCount = 0;

void addQuadruple(char op, char arg1, char arg2, char result) {
    quadruples[quadrupleCount].op = op;
    quadruples[quadrupleCount].arg1 = arg1;
    quadruples[quadrupleCount].arg2 = arg2;
    quadruples[quadrupleCount].result = result;
    quadrupleCount++;
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH];

    printf("Enter an expression: ");
    fgets(expression, MAX_EXPRESSION_LENGTH, stdin);

    int len = strlen(expression);

    char tempResult = 'T';
    char tempArg1, tempArg2;
    int isTempArg1 = 0;

    for (int i = 0; i < len; i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            tempArg1 = expression[i - 1];
            tempArg2 = expression[i + 1];
            if (tempArg1 == tempResult) {
                isTempArg1 = 1;
            }
            else {
                addQuadruple(expression[i], tempResult, tempArg2, tempResult);
                isTempArg1 = 0;
            }
            expression[i - 1] = tempResult;
            for (int j = i; j < len - 2; j++) {
                expression[j] = expression[j + 2];
            }
            len -= 2;
            i--;
            tempResult++;
        }
    }

    if (isTempArg1) {
        addQuadruple(expression[0], tempArg1, expression[2], tempResult - 1);
    }
    else {
        addQuadruple(expression[0], expression[2], tempArg2, tempResult - 1);
    }

    printf("Quadruples:\n");
    for (int i = 0; i < quadrupleCount; i++) {
        printf("(%c, %c, %c, %c)\n", quadruples[i].op, quadruples[i].arg1, quadruples[i].arg2, quadruples[i].result);
    }

    return 0;
}

