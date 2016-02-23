#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char action[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int from[2] = {0, 0};
    int to[2] = {0, 0};

    while ((read = getline(&line, &len, stdin)) != -1) {
        sscanf(line, "%[ togleurnf] %d,%d through %d,%d", action, &from[0], &from[1], &to[0], &to[1]);
        printf("action: %s, range: %d:%d->%d:%d\n", action, from[0], from[1], to[0], to[1]);
    }
    return 0;
}
