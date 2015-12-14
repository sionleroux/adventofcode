#include <stdio.h>

int totalPaper(int, int, int);
int smallestSide(int, int, int);
int smallestPerimiter(int, int, int);
int cubicVolume(int, int, int);

int main()
{
    int tp = 0; // total paper counter
    int p = 0; // current paper counter
    int tr = 0; // total ribbon counter
    int r = 0; // current ribbon counter
    int d[3] = {0, 0, 0}; // dimensions

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        printf("Retrieved line of length %zu: %s", read, line);
        sscanf(line, "%dx%dx%d", &d[0], &d[1], &d[2]);
        printf("x:%d, y:%d, z:%d\n", d[0], d[1], d[2]);
        p = totalPaper(d[0], d[1], d[2]);
        r =
            smallestPerimiter(d[0], d[1], d[2]) +
            cubicVolume(d[0], d[1], d[2]);
        printf("paper: %d\n", p);
        printf("ribbon: %d\n", r);
        tp = tp+p;
        tr = tr+r;
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
int totalPaper(int x, int y, int z) {

    int a = x*y;
    int b = x*z;
    int c = z*y;

    // get smallest side
    int s = smallestSide(a, b, c);

    return 2*a + 2*b + 2*c + s;
}

/**
 * Simply returns the smallest of 3 numbers.
 * Would be cool if it could do an array of arbitrary size.
 * Used for finding which side of a cuboid is smallest.
 * Uses <= instead of < because somesides small sides have equal length
 */
int smallestSide(int a, int b, int c) {
    if (a <= b && a <= c) {
        return a;
    } else if (b <= a && b <= c) {
        return b;
    } else {
        return c;
    }
}

/**
 * Excludes the biggest number and multiplies the rest by 2 to find
 * the smallest perimiter.  This algorithm is not dry at all :-(
 */
int smallestPerimiter(int a, int b, int c) {
    if (a >= b && a >= c) {
        return 2*(b+c);
    } else if (b >= a && b >= c) {
        return 2*(a+c);
    } else {
        return 2*(a+b);
    }
}

/**
 * Multiple X, Y & Z to get volume (for the bow in the ribbon)
 */
int cubicVolume(int a, int b, int c) {
    return a * b * c;
}
