#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned short parse(char[2]);

int main(int argc, char *argv[]) {
    unsigned short result = parse("g");
    printf("result: %hu\n", result);
    return 0;
}

unsigned short parse(char target[2]) {
    printf("PARSING FOR: '%s'\n", target);
    int type = 0;

    // if the input is entirely a number, then just send it back
    if (isdigit(target[0])) {
        return atoi(target);
    }

    char artarget[5];
    artarget[0] = '-';
    artarget[1] = '>';
    artarget[2] = ' ';
    artarget[3] = 0;
    artarget[4] = 0;

    strcat(artarget, target);

    FILE *input;
    input = fopen("input.txt", "r");
    char line[20];
    if (input == NULL) {
        puts("Error opening file!");
        return -2;
    }

    const int num_opers = 5;
    const char *logics[num_opers];
    logics[0] = "OR";
    logics[1] = "AND";
    logics[2] = "NOT";
    logics[3] = "LSHIFT";
    logics[4] = "RSHIFT";

    while (fgets(line, sizeof(line), input)) {

        type = 0;
        printf("line: %s", line);

        if (strstr(line, artarget)) {
            printf("this is the string you are looking for: %s\n", target);

            for (int i = 0; i < num_opers; ++i) {
                if (strstr(line, logics[i])) {
                    puts("it was an operator");
                    type = 1;

                    char left[2] = {0, 0};
                    char right[2] = {0, 0};
                    unsigned short l, r = 0;

                    switch (i) {
                        case 0:
                            sscanf(line, "%s OR %s", left, right);
                            puts("AND!");
                            puts(left);
                            puts(right);
                            l = parse(left);
                            r = parse(right);
                            return l | r;
                        case 1:
                            sscanf(line, "%s AND %s", left, right);
                            l = parse(left);
                            r = parse(right);
                            return l & r;
                        case 2:
                            sscanf(line, "NOT %s", right);
                            r = parse(right);
                            return ~r;
                        case 3:
                            sscanf(line, "%s LSHIFT %s", left, right);
                            printf("right: %s\n", right);
                            l = parse(left);
                            r = parse(right);
                            printf("%hu shifted left by %hu\n", l, r);
                            return l << r;
                        case 4:
                            sscanf(line, "%s RSHIFT %s", left, right);
                            l = parse(left);
                            r = parse(right);
                            return l >> r;
                    }

                    break;
                }
            }

            if (type == 0) {
                if (isdigit(line[0])) {
                    printf("it was a number: ");
                    type = 2;

                    unsigned short val;
                    char name[2]; //XXX keeping this cos too lazy to code it out
                    sscanf(line, "%hu -> %s", &val, name );

                    fclose(input);
                    printf("%hu\n", val);
                    return val;
                }
            }

            if (type == 0) {
                printf("it was a wire: ");
                type = 3;

                char whence[2]; // get value from here
                char name[2]; //XXX keeping this cos too lazy to code it out
                sscanf(line, "%s -> %s", whence, name );
                printf("whence >%s<\n", whence);

                unsigned short result = parse(whence);
                fclose(input);
                printf("%hu\n", result);
                return result;
            }

        }

    }

    fclose(input);
    return -1;
}
