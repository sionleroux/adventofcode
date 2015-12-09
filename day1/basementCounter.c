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

        // as soon as we're below ground (-1) output how many instructions it took
        if (f < 0) {
            printf("floor: %d\n", f);
            printf("position: %d\n", p);
            return 0;
        }

    } while (c != EOF);
    fclose(input);

    puts("Never went below ground level or I screwed up counting");
    return 2;
}
