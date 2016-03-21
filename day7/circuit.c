#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// typedefs
typedef struct wire wire;
struct wire {
    char name[2];
    unsigned int value;
};

int main(int argc, char *argv[]) {

    const int num_opers = 5;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    const char *logics[num_opers];

    logics[0] = "OR";
    logics[1] = "AND";
    logics[2] = "NOT";
    logics[3] = "LSHIFT";
    logics[4] = "RSHIFT";

    int type;

    wire wires[10];
    int wirecount = 0;

    while ((read = getline(&line, &len, stdin)) != -1) {
        type = 0;

        printf("line: %s", line);

        for (int i = 0; i < num_opers; ++i) {
            if (strstr(line, logics[i])) {
                //TODO determine which operator it is
                puts("it was an operator");
                type = 1;
            }
        }

        if (type == 0) {
            if (isdigit(line[0])) {
                puts("it was a number");
                type = 2;

                int val;
                char name[2];
                sscanf(line, "%d -> %s", &val, name );
                strcpy(wires[wirecount].name, name);
                wires[wirecount].value = val;

                wirecount++;
            }
        }

        if (type == 0) {
            puts("it was something else");
        }
    }

    for (int i = 0; i < wirecount; ++i) {
        printf("%s:%d\n", wires[i].name, wires[i].value);
    }

    return 0;
}
