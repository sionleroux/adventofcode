#include <stdio.h>

int main()
{
    FILE *input;
    char c; // character as read from input
    int n = 0; // counter

    input = fopen("input.txt", "r");
    if (input == NULL) {
        puts("Error opening file!");
        return 1;
    }

    do {
        c = fgetc(input);
        // "(" is up and ")" is down
        if (c == '(') {
            n++;
        } else if (c == ')') {
            n--;
        }
    } while (c != EOF);
    fclose(input);

    printf("floor: %d\n", n);

    return 0;
}
