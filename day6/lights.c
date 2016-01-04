#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char action[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    float from;
    float to;

    while ((read = getline(&line, &len, stdin)) != -1) {
        sscanf(line, "%s %f through %f", action, &from, &to);
        printf("action: %s, range: %f->%f\n", action, from, to);
    }

    return 0;
}
