#include <stdio.h>

int main() {
    int x = 5;
    int y = 10;
    int z;

    if (x > y) {
        z = x + y;
    } else {
        z = x - y;
    }

    // Dead code, as z has already been assigned a value
    if (x < y) {
        z = x * y;
    }

    printf("z = %d\n", z);

    return 0;
}

