#include <stdio.h>
#include <string.h>

// globals
FILE *input; // input

int main(void) {
    char c; // char from input
    int sides[3][3]; // triangle sides
    int i = 0; // counter of totals
    int t = 0; // counter for whole triangles

    // open file
    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    while ((c = fscanf(input, "%d %d %d",
            &sides[t][0],
            &sides[t][1],
            &sides[t][2])) != EOF) {
        if (++t > 2) {
            t = 0;
            for (int s = 0; s < 3; ++s) {
                if (
                        (sides[0][s] + sides[1][s] > sides[2][s]) &&
                        (sides[0][s] + sides[2][s] > sides[1][s]) &&
                        (sides[1][s] + sides[2][s] > sides[0][s])
                ) i++;
            }
        }
    }

    printf("%d\n", i);

    fclose(input);
    return 0;
}
