#include <stdio.h>
#include <stdlib.h>

#define VERBOSE 2 // verbosit level (lots of output trips at 2)
#define CUBOID 3 // a cuboid has 3 dimensions: x,y,z

int totalPaper(int*);
int smallestPerimiter(int*);
int cubicVolume(int*);
int compare_ints(const void*, const void*);

int main()
{
    int tp = 0; // total paper counter
    int p = 0; // current paper counter
    int tr = 0; // total ribbon counter
    int r = 0; // current ribbon counter
    int d[CUBOID] = {0, 0 ,0}; // dimensions

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        sscanf(line, "%dx%dx%d", &d[0], &d[1], &d[2]);
        qsort(d, CUBOID, sizeof(int), compare_ints);
        p = totalPaper(d);
        r = smallestPerimiter(d) + cubicVolume(d);
        tp = tp+p;
        tr = tr+r;
#if VERBOSE >= 2
        printf("dimensions: x:%d, y:%d, z:%d\n", d[0], d[1], d[2]);
        printf("Retrieved line of length %zu: %s", read, line);
        printf("sorted: x:%d, y:%d, z:%d\n", d[0], d[1], d[2]);
        printf("paper: %d\n", p);
        printf("ribbon: %d\n", r);
#endif
    }

    printf("total paper: %d\n", tp); // correct: 1588178
    printf("total ribbon: %d\n", tr); // correct: 3783758

    return 0;
}

/**
 * Calculate the wrapping paper needed for a box.
 * Done by summing:
 *   - area of the cuboid 2xy + 2yz + 2xz
 *   - some slack (the area of the smallest side)
 */
int totalPaper(int* d) {

    int a = d[0]*d[1];
    int b = d[0]*d[2];
    int c = d[1]*d[2];

#if VERBOSE >= 2
    printf("Smallest of %dx%dx%d is: %d\n", a, b, c, a);
#endif

    return 2*a + 2*b + 2*c + a; // a is the smallest side
}

/**
 * Excludes the biggest number and multiplies the rest by 2 to find
 * the smallest perimiter.
 */
int smallestPerimiter(int* d) {
    return 2 * (d[0] + d[1]);
}

/**
 * Multiple X, Y & Z to get volume (for the bow in the ribbon)
 */
int cubicVolume(int* d) {
    int v = 1; // volume holder
    for (int i = 0; i < CUBOID; ++i) {
        v *= d[i];
    }
    return v;
}

/**
 * No fancy safeguard tricks here because for this program I know my
 * ints will always be positive (a box can't have negative dimensions)
 */
int compare_ints(const void* a, const void* b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x - *y;
}
