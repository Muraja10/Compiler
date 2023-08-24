#include <stdio.h>

int main() {
    char input[1000];
    printf("Enter a string:\n");
    fgets(input, sizeof(input), stdin);

    int whitespaceCount = 0;
    int newlineCount = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ') {
            whitespaceCount++;
        } else if (input[i] == '\n') {
            newlineCount++;
        }
    }

    printf("Whitespace count: %d\n", whitespaceCount);
    printf("Newline count: %d\n", newlineCount);

    return 0;
}
