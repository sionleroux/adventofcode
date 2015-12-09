#include <stdio.h>

int main()
{
    FILE *input;
    char c; // character as read from input
    int f = 0; // what floor Santa is on
    int p = 0; // how many instructions we've read

    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    do {
        c = fgetc(input);
        p++; // moves as we read each instruction

        // "(" is up and ")" is down
        if (c == '(') {
            f++;
        } else if (c == ')') {
            f--;
        }

    } while (c != EOF && f >= 0); // also step out if Santa steps below ground
    fclose(input);

    if (c == EOF) {
        puts("never went below ground or counting mistake");
        return 1;
    }

    printf("floor: %d\n", f);
    printf("position: %d\n", p);
    return 0;
}
