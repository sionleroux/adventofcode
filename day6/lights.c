#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int on = 1;
const int off = 0;

void turn_on(int[][1000], int[], int[]);
void turn_off(int[][1000], int[], int[]);
void toggle(int[][1000], int[], int[]);
int count(int[][1000]);
void init(int[][1000]);

int main(int argc, char *argv[])
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char action[8];
    int lights[1000][1000];
    int from[2] = {0, 0};
    int to[2] = {0, 0};

    init(lights);

    while ((read = getline(&line, &len, stdin)) != -1) {
        sscanf(line, "%[ togleurnf] %d,%d through %d,%d", action, &from[0], &from[1], &to[0], &to[1]);

        if (strcmp(action, "turn on ") == 0) {
            turn_on(lights, from, to);
        } else if (strcmp(action, "turn off ") == 0) {
            turn_off(lights, from, to);
        } else if (strcmp(action, "toggle ") == 0) {
            toggle(lights, from, to);
        } else {
            puts("bad action");
            return 1;
        }

    }

    printf("%d\n", count(lights));

    return 0;
}

void init(int lights[][1000]) {
    for (int x = 0; x <= 999; ++x) {
        for (int y = 0; y <= 999; ++y) {
            lights[x][y] = 0;
        }
    }
}

void turn_on(int lights[][1000], int from[], int to[]) {
    for (int x = from[0]; x <= to[0]; ++x) {
        for (int y = from[1]; y <= to[1]; ++y) {
            lights[x][y] = on;
        }
    }
}

void turn_off(int lights[][1000], int from[], int to[]) {
    for (int x = from[0]; x <= to[0]; ++x) {
        for (int y = from[1]; y <= to[1]; ++y) {
            lights[x][y] = off;
        }
    }
}

void toggle(int lights[][1000], int from[], int to[]) {
    for (int x = from[0]; x <= to[0]; ++x) {
        for (int y = from[1]; y <= to[1]; ++y) {
            lights[x][y] = !lights[x][y];
        }
    }
}

int count(int lights[][1000]) {
    int c = 0;

    for (int x = 0; x <= 999; ++x) {
        for (int y = 0; y <= 999; ++y) {
            if (lights[x][y] == on) c++;
        }
    }

    return c;
}
