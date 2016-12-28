#include <stdio.h>
#include <string.h>

// globals
FILE *input; // input

int main(void) {
    char c; // char from input
    int x, y, z; // triangle sides
    int i = 0; // counter

    // open file
    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    while ((c = fscanf(input, "%d %d %d", &x, &y, &z)) != EOF) {
        if ((x + y > z) && (x + z > y) && (z + y > x)) i++;
    }

    printf("%d\n", i);

    fclose(input);
    return 0;
}
